# SOLID Principles

Source Article: [SOLID Principles](https://medium.com/@shivambhadani_/solid-principles-demystified-finally-understand-oops-design-the-right-way-8443fc642630)
## Contents

- [Single Responsibility Principle (SRP)](#single-responsibility-principle-srp)
- [Open/Closed Principle (OCP)](#openclosed-principle-ocp)
- [Liskov Substitution Principle (LSP)](#liskov-substitution-principle-lsp)
- [Interface Segregation Principle (ISP)](#interface-segregation-principle-isp)
- [Dependency Inversion Principle (DIP)](#dependency-inversion-principle-dip)
- [Short Revision](#short-notes-5-min-revision)

---
## Short Notes (5 min revision)

### Single Responsibility Principle (SRP)
> Signs of Violations:
 - A class has multiple reasons or sources of change (e.g., a TicketBooking class that handles price policies, payment gateways, and notifications).
 - Mixing business logic with infrastructure logic (e.g., having user data logic in the same class as S3 image uploading or DB deletion).
 - Handling integration with multiple external providers in one place (e.g., an email, SMS, and push notification sender in a single class)

> Implementation Patterns:
 - Ask yourself: "Will there be only one reason if I want to touch the code of this class in the future?" If yes, you are following SRP.
 - Split the large class into smaller, focused classes where each handles a single responsibility.
 - Use a main class to coordinate the smaller, single-responsibility classes


### Open/Closed Principle (OCP)
> Signs of Violations:
 - You are frequently modifying existing, tested classes to add new features.
 - Your code relies heavily on adding if-else or switch statements to decide behavior when a new type (like a new payment method or discount) is introduced

> Implementation Patterns:
 - Rely on abstractions (interfaces or base classes) rather than concrete implementations.
 - Extend behavior by creating new classes that implement the abstraction, completely leaving the existing classes unmodified.


### Liskov Substitution Principle (LSP)
> Signs of Violations:
 - A child class behaves unexpectedly when used in place of its parent (e.g., a Square class changing the area calculation behavior expected from a Rectangle).
 - A derived class throws exceptions for methods it inherits but cannot logically perform.
 - Inheritance is only syntactically valid but behaviorally incorrect

> Implementation Patterns:
 - Ensure child classes strictly respect the behavior and expectations of their parent classes.
 - Test your code by replacing the parent class with all child classes; if the program works without bugs or surprises, LSP is satisfied

### Interface Segregation Principle (ISP)
> Signs of Violations:
 - Classes are forced to depend on or implement interface methods they do not actually use.
 - You find yourself writing empty methods or throwing runtime_error("Not implemented") just to satisfy an interface contract
 - Large, monolithic interfaces ("fat interfaces") that try to cover too many use cases (like a payment gateway interface forcing a Cash on Delivery class to implement a refund() method)

> Implementation Patterns:
 - Break down large interfaces into smaller, highly focused, role-based contracts.
 - Only require classes to implement exactly what they need

### Dependency Inversion Principle (DIP)
> Signs of Violations:
 - High-level business logic (Service Layer) directly depends on and instantiates low-level concrete classes (Repository Layer/Databases).
 - Tight coupling makes it difficult to switch out underlying technologies (e.g., moving from MySQL to MongoDB) or write tests

> Implementation Patterns:
 - Both high-level and low-level modules should depend on abstractions (interfaces).
 - Create an interface for the low-level operations, implement it in a concrete class, and inject that dependency into your high-level business logic (example: ITicketRepository, TicketRepository, ServiceLayer, Controller all separated ).


---

# Single Responsibility Principle (SRP)

## Definition

> **A class should have only one reason to change.**

This means a class should contain only those methods that are impacted by a **single source of change**.

Simply put:

If in the future you need to modify a class, that modification should happen due to **one reason only**, not multiple unrelated reasons.

The definition sounds confusing at first, so let’s understand it with examples.

---

### Example 1 — Violating SRP

```cpp
#include <iostream>
using namespace std;

class TicketBooking {
private:
    int movieId;
    int userId;
    string seatNumber;

public:
    TicketBooking(int mId, int uId, string seat)
        : movieId(mId), userId(uId), seatNumber(seat) {}

    bool checkSeatAvailability() {
        // Logic to check seat in DB
        return true;
    }

    int calculatePrice() {
        // Price logic based on seat type, timing
        return 300;
    }

    bool makePayment() {
        // Call payment gateway API
        return true;
    }

    void sendConfirmation() {
        // Send SMS or Email
    }

    void book() {
        if (checkSeatAvailability()) {
            int price = calculatePrice();
            bool paid = makePayment();
            if (paid) {
                sendConfirmation();
                cout << "Booking successful!" << endl;
            }
        }
    }
};
```

The above code violates SRP because it has 4 logical reasons to change:

- Seat checking logic changes  
- Price policy changes  
- Payment gateway changes  
- Notification/confirmation logic changes  

Payment and price are handled by different teams, so if tomorrow the payment method changes or the price policy changes, you need to modify the `TicketBooking` class. There are 4 sources that can change the code of this class, so this violates SRP. One class should only change due to one source.

To correct the above code, we need to split it into multiple classes where each class can only be changed due to a single source or reason.

```cpp
#include <iostream>
using namespace std;

class SeatChecker {
public:
    bool isSeatAvailable(int movieId, string seatNumber) {
        // Check in DB if seat is free
        return true;
    }
};

class PriceCalculator {
public:
    int getPrice(int movieId, string seatNumber) {
        // Logic based on seat type, timing, etc.
        return 300;
    }
};

class PaymentService {
public:
    bool pay(int userId, int amount) {
        // Payment gateway integration
        cout << "Processing payment of ₹" << amount 
             << " for user " << userId << endl;
        return true;
    }
};

class Notifier {
public:
    void sendConfirmation(int userId, int movieId) {
        // Send email/SMS
        cout << "Confirmation sent to user "
             << userId << " for movie "
             << movieId << endl;
    }
};
```

Now, the `TicketBooking` class coordinates everything:

```cpp
class TicketBooking {
private:
    SeatChecker seatChecker;
    PriceCalculator priceCalculator;
    PaymentService paymentService;
    Notifier notifier;

public:
    void bookTicket(int userId, int movieId, string seatNumber) {
        if (seatChecker.isSeatAvailable(movieId, seatNumber)) {
            int price = priceCalculator.getPrice(movieId, seatNumber);
            bool paid = paymentService.pay(userId, price);

            if (paid) {
                notifier.sendConfirmation(userId, movieId);
                cout << "Booking successful!" << endl;
            } else {
                cout << "Payment failed!" << endl;
            }
        } else {
            cout << "Seat not available!" << endl;
        }
    }
};
```

Most people confuse SRP by thinking that a class should only contain one method, but that’s wrong. It can have multiple methods.  

Some people think SRP means a class handles only a single thing. But thinking like that is very confusing.

Just remember that SRP means a class should only contain that set of methods which change in future due to a single source or reason.

---

### Example 2

```cpp
#include <vector>
#include <algorithm>
using namespace std;

class Order {
private:
    vector<string> items;

public:
    void addItem(string item) {
        items.push_back(item);
    }

    void removeItem(string item) {
        items.erase(
            remove(items.begin(), items.end(), item),
            items.end()
        );
    }

    int getTotalPrice() {
        return items.size() * 100;
    }
};
```

Does the above code violate SRP?  
**No.**

All methods are related to one thing: managing the contents of an Order.

One reason to change:  
If business rules about orders (like pricing, item handling) change.

---

### Example 3 — Violating SRP

```cpp
class UserProfileManager {
public:
    void getProfile(int userId) {
        // Fetch user from DB
    }

    void updateProfile(int userId) {
        // Save new user profile
    }

    void uploadProfilePicture(int userId) {
        // Save image to S3
    }

    void deleteAccount(int userId) {
        // Delete user from DB and clear sessions
    }
};
```

All methods seem “user-related” — so developers assume it’s a single responsibility. But it is not following SRP.

- `getProfile`, `updateProfile` change when user data logic changes.  
- `uploadProfilePicture` changes when infrastructure changes (e.g., S3 to another storage).  
- `deleteAccount` changes when business policy changes.  

Since the above class has 3 reasons to change, it has to be split into 3 separate classes.

```cpp
class UserProfileService {
public:
    void get(int userId) { /* ... */ }
    void update(int userId) { /* ... */ }
};

class UserPictureService {
public:
    void upload(int userId) { /* upload to S3 */ }
};

class UserAccountManager {
public:
    void remove(int userId) { /* delete from DB, sessions */ }
};
```

---

### Example 4 — Violating SRP

```cpp
class NotificationService {
public:
    void sendEmail(string to, string message) {
        // Send email
    }

    void sendSMS(string to, string message) {
        // Send SMS
    }

    void sendPush(string to, string message) {
        // Push notification
    }
};
```

The above code is also violating SRP.

Suppose you use different providers for email, SMS, and push notifications. If any provider changes, this class changes. That means multiple sources of change.

We split it into separate classes:

```cpp
class EmailSender {
public:
    void send(string to, string message) { /* ... */ }
};

class SmsSender {
public:
    void send(string to, string message) { /* ... */ }
};

class PushSender {
public:
    void send(string to, string message) { /* ... */ }
};
```

---

### Example 5 — Blog Service (Violating SRP)

```cpp
#include <iostream>
using namespace std;

class BlogService {
public:
    void createPost(string title, string content) {
        cout << "Post saved to DB" << endl;
    }

    void updatePost(int postId, string content) {
        cout << "Post updated" << endl;
    }

    void deletePost(int postId) {
        cout << "Post deleted" << endl;
    }

    void publish(int postId) {
        cout << "Post published" << endl;
    }

    void unpublish(int postId) {
        cout << "Post unpublished" << endl;
    }

    string generateShareLink(int postId) {
        return "https://blog.com/share/" + to_string(postId);
    }

    void postToTwitter(int postId) {
        string link = generateShareLink(postId);
        cout << "Tweet posted with link: " << link << endl;
    }

    void notifyFollowers(int postId) {
        cout << "Followers notified via email/SMS" << endl;
    }

    void notifyAdmins(int postId) {
        cout << "Admins notified" << endl;
    }
};
```

Above code violates SRP.

- CRUD methods change when DB changes.  
- Publish/unpublish changes when business logic changes.  
- Sharing logic changes when external APIs change.  
- Notification logic changes when communication logic changes.  

We split it:

```cpp
class PostRepository {
public:
    void create(string title, string content) {
        cout << "Post saved to DB" << endl;
    }

    void update(int postId, string content) {
        cout << "Post updated" << endl;
    }

    void remove(int postId) {
        cout << "Post deleted" << endl;
    }
};

class PublisherService {
public:
    void publish(int postId) {
        cout << "Post published" << endl;
    }

    void unpublish(int postId) {
        cout << "Post unpublished" << endl;
    }
};

class SharingService {
public:
    string generateShareLink(int postId) {
        return "https://blog.com/share/" + to_string(postId);
    }

    void postToTwitter(int postId) {
        string link = generateShareLink(postId);
        cout << "Tweet posted with link: " << link << endl;
    }
};

class BlogNotificationService {
public:
    void notifyFollowers(int postId) {
        cout << "Followers notified via email/SMS" << endl;
    }

    void notifyAdmins(int postId) {
        cout << "Admins notified" << endl;
    }
};
```

---

### Final Rule to Remember

After writing a class, ask yourself:

> Will there be only one reason if I want to touch the code of this class in the future?

If the answer is **Yes**, then your code is following **SRP**.


# Open/Closed Principle (OCP)

## Definition

> **Software entities (classes, modules, functions) should be open for extension, but closed for modification.**

### What does it actually mean?

- **Open for extension** → You can add new functionality  
- **Closed for modification** → You should not change existing tested code to do it  

**Goal:** Add new features without breaking existing logic.

---

## ❌ Violating OCP

```cpp
#include <iostream>
using namespace std;

class PaymentProcessor {
public:
    void process(string paymentMethod) {
        if (paymentMethod == "credit_card") {
            cout << "Processing credit card payment..." << endl;
        } 
        else if (paymentMethod == "paypal") {
            cout << "Processing PayPal payment..." << endl;
        } 
        else if (paymentMethod == "upi") {
            cout << "Processing UPI payment..." << endl;
        } 
        else {
            throw invalid_argument("Unsupported payment method");
        }
    }
};
```

### Why This Violates OCP

Every time a new method (like Stripe, Crypto Pay) is added, you have to:

- Modify this class  
- Risk breaking existing code  
- Add more `if-else`  

It is neither scalable nor maintainable.

---

## ✅ Refactored Version (Following OCP)

Instead of implementing every payment method inside `PaymentProcessor`, we use abstraction.

```cpp
#include <iostream>
using namespace std;

// Abstraction
class PaymentStrategy {
public:
    virtual void pay() = 0;
    virtual ~PaymentStrategy() {}
};

// Concrete implementations
class CreditCardPayment : public PaymentStrategy {
public:
    void pay() override {
        cout << "Credit card payment processed" << endl;
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay() override {
        cout << "PayPal payment processed" << endl;
    }
};

class UPIPayment : public PaymentStrategy {
public:
    void pay() override {
        cout << "UPI payment processed" << endl;
    }
};

// Closed for modification
class PaymentProcessor {
private:
    PaymentStrategy* strategy;

public:
    PaymentProcessor(PaymentStrategy* s) : strategy(s) {}

    void process() {
        strategy->pay();
    }
};
```

### Usage

```cpp
int main() {
    UPIPayment upi;
    PaymentProcessor processor(&upi);
    processor.process();
}
```

If we add `CryptoPayment` in the future:

- No change to `PaymentProcessor`
- Just create a new class implementing `PaymentStrategy`

That’s **Open for extension, Closed for modification** ✅

---

### More Examples

---

### Example 1: Discount Engine

#### ❌ Violating OCP

```cpp
class DiscountEngine {
public:
    double calculateDiscount(string type, double amount) {
        if (type == "student") {
            return amount * 0.1;
        } 
        else if (type == "seasonal") {
            return amount * 0.2;
        }
        return 0;
    }
};
```

Every time a new discount is added, this class must be changed → violates OCP.

---

#### ✅ Refactored Version

```cpp
// Abstraction
class DiscountStrategy {
public:
    virtual double getDiscount(double amount) = 0;
    virtual ~DiscountStrategy() {}
};

class StudentDiscount : public DiscountStrategy {
public:
    double getDiscount(double amount) override {
        return amount * 0.1;
    }
};

class SeasonalDiscount : public DiscountStrategy {
public:
    double getDiscount(double amount) override {
        return amount * 0.2;
    }
};

class NoDiscount : public DiscountStrategy {
public:
    double getDiscount(double amount) override {
        return 0;
    }
};

class DiscountEngine {
private:
    DiscountStrategy* strategy;

public:
    DiscountEngine(DiscountStrategy* s) : strategy(s) {}

    double applyDiscount(double amount) {
        return amount - strategy->getDiscount(amount);
    }
};
```

### Usage

```cpp
int main() {
    StudentDiscount student;
    DiscountEngine engine(&student);

    cout << engine.applyDiscount(500) << endl; // 450
}
```

Add new discount → create new class.  
No modification to `DiscountEngine`.

---

### Example 2: Notification System

We want to support multiple notification types like Email, SMS, Push, etc.

```cpp
#include <vector>

// Abstraction
class Notifier {
public:
    virtual void notify(string userId, string message) = 0;
    virtual ~Notifier() {}
};

class EmailNotifier : public Notifier {
public:
    void notify(string userId, string message) override {
        cout << "Email to " << userId << ": " << message << endl;
    }
};

class SMSNotifier : public Notifier {
public:
    void notify(string userId, string message) override {
        cout << "SMS to " << userId << ": " << message << endl;
    }
};

class PushNotifier : public Notifier {
public:
    void notify(string userId, string message) override {
        cout << "Push notification to " << userId << ": " 
             << message << endl;
    }
};

class NotificationService {
private:
    vector<Notifier*> notifiers;

public:
    NotificationService(vector<Notifier*> n) : notifiers(n) {}

    void sendNotification(string userId, string message) {
        for (auto notifier : notifiers) {
            notifier->notify(userId, message);
        }
    }
};
```

To add a new notifier:

- Create a new class implementing `Notifier`
- Do NOT modify `NotificationService`

That’s OCP.

---

# Final Things to Remember

- Don’t use `if-else` or `switch` to decide behavior.
- Don’t edit existing classes to add new cases.
- Use **abstractions (interfaces / base classes)**.
- Extend behavior by creating new classes.

If your existing tested class does not need modification when adding new features —  
you are following **OCP**.

# Liskov Substitution Principle (LSP)

## Definition

> **If S is a subtype of T, then objects of type T should be replaceable with objects of type S without breaking the program.**

### In simple English

You should be able to use a child class anywhere the parent class is expected, and it should work the same — without surprises, bugs, or broken behavior.

### Idea Behind LSP

- Child classes should respect the behavior expected from their parent.
- Inheritance should be behaviorally correct, not just syntactically valid.
- If a derived class violates the expectations of the base class, it breaks LSP.

Even if the theory feels abstract, the examples will make it crystal clear.

---

### ❌ Classic Rectangle–Square Problem (Violates LSP)

```cpp
#include <iostream>
using namespace std;

class Rectangle {
protected:
    int width;
    int height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    virtual void setWidth(int w) {
        width = w;
    }

    virtual void setHeight(int h) {
        height = h;
    }

    int getArea() const {
        return width * height;
    }
};

class Square : public Rectangle {
public:
    Square(int side) : Rectangle(side, side) {}

    void setWidth(int w) override {
        width = w;
        height = w;
    }

    void setHeight(int h) override {
        width = h;
        height = h;
    }
};

void printArea(Rectangle& rect) {
    rect.setWidth(5);
    rect.setHeight(10);
    cout << rect.getArea() << endl; // Expected 50
}

int main() {
    Rectangle rect(2, 3);
    printArea(rect);   // OK → 50

    Square square(2);
    printArea(square); // Wrong → 100
}
```

### Why This Breaks LSP

`printArea()` expects Rectangle behavior.  
But when we pass a `Square`, behavior changes unexpectedly.

So even though Square **is-a** Rectangle syntactically,  
it is not behaviorally substitutable.

---

### ✅ Refactored Version (Following LSP)

```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    virtual int getArea() const = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape {
private:
    int width;
    int height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    int getArea() const override {
        return width * height;
    }
};

class Square : public Shape {
private:
    int side;

public:
    Square(int s) : side(s) {}

    int getArea() const override {
        return side * side;
    }
};

void printArea(const Shape& shape) {
    cout << shape.getArea() << endl;
}

int main() {
    printArea(Rectangle(5, 10)); // 50
    printArea(Square(10));       // 100
}
```

Now replacing `Shape` with any derived class does not break behavior.

That’s LSP.

---

### Example 1 — Notification Service

### ❌ Violating LSP

```cpp
#include <iostream>
using namespace std;

class NotificationService {
public:
    virtual void send(string userId, string message) = 0;
    virtual ~NotificationService() {}
};

class EmailService : public NotificationService {
public:
    void send(string userId, string message) override {
        cout << "Email sent" << endl;
    }
};

class DummyNotification : public NotificationService {
public:
    void send(string userId, string message) override {
        throw runtime_error("Disabled in testing environment");
    }
};

void notify(NotificationService& service) {
    service.send("u123", "Your ticket is booked");
}
```

If `DummyNotification` throws an exception, replacing the base type causes runtime failure → LSP violation.

---

### ✅ Fixed Version

```cpp
class DummyNotification : public NotificationService {
public:
    void send(string userId, string message) override {
        cout << "[Testing Environment] Notification skipped" << endl;
    }
};
```

Now substitution works without breaking behavior.
Maybe the above example will seem very intuitive, but the crux is that always try to replace the parent class with all child classes. If everything is working fine, then your code is obeying LSP.

---

# Interface Segregation Principle (ISP)

### Definition

> **Clients should not be forced to depend on interfaces they do not use.**

### In simple English

Don’t make classes implement methods they don’t need.  
Break large interfaces into smaller, focused ones.

---

### ❌ Example 1 — Payment Gateway (Violates ISP)

```cpp
class PaymentGateway {
public:
    virtual void pay() = 0;
    virtual void refund() = 0;
    virtual void schedule() = 0;
};
```

Now:

- Stripe → supports all
- CashOnDelivery → supports only `pay()`

```cpp
class CashOnDelivery : public PaymentGateway {
public:
    void pay() override {
        cout << "COD payment" << endl;
    }

    void refund() override {
        throw runtime_error("Refund not supported");
    }

    void schedule() override {
        throw runtime_error("Scheduling not supported");
    }
};
```

This violates ISP.

---

### ✅ Fixed Version

```cpp
class Payable {
public:
    virtual void pay() = 0;
    virtual ~Payable() {}
};

class Refundable {
public:
    virtual void refund() = 0;
};

class Schedulable {
public:
    virtual void schedule() = 0;
};

class CashOnDelivery : public Payable {
public:
    void pay() override {
        cout << "COD payment" << endl;
    }
};

class StripePayment : public Payable, public Refundable, public Schedulable {
public:
    void pay() override {}
    void refund() override {}
    void schedule() override {}
};
```

---

### Example 2 — Report Generator

### ❌ Violating ISP

```cpp
class ReportGenerator {
public:
    virtual void generatePDF() = 0;
    virtual void generateExcel() = 0;
    virtual void generateCSV() = 0;
};
```

If a class only needs CSV, it is forced to implement all.

---

### ✅ Fixed Version

```cpp
class PDFGeneratable {
public:
    virtual void generatePDF() = 0;
};

class ExcelGeneratable {
public:
    virtual void generateExcel() = 0;
};

class CSVGeneratable {
public:
    virtual void generateCSV() = 0;
};

class UserActivityReport : public CSVGeneratable {
public:
    void generateCSV() override {
        cout << "Generating user CSV" << endl;
    }
};

class BillingReport : public PDFGeneratable,
                      public ExcelGeneratable,
                      public CSVGeneratable {
public:
    void generatePDF() override {}
    void generateExcel() override {}
    void generateCSV() override {}
};
```

---

### Example 3 — File Handler

### ❌ Violating ISP

```cpp
class FileHandler {
public:
    virtual void open() = 0;
    virtual string read() = 0;
    virtual void write(string data) = 0;
    virtual void close() = 0;
};
```

Reader classes are forced to implement `write()`.

---

### ✅ Fixed Version

```cpp
class FileOpener {
public:
    virtual void open() = 0;
    virtual void close() = 0;
};

class FileReader : public FileOpener {
public:
    virtual string read() = 0;
};

class FileWriter : public FileOpener {
public:
    virtual void write(string data) = 0;
};

class LogFileReader : public FileReader {
public:
    void open() override {}
    string read() override { return "log"; }
    void close() override {}
};
```

---

### Remember ISP

- Split large interfaces into small role-based contracts
- Don’t force classes to depend on things they don’t use
- Avoid `throw runtime_error("Not implemented")`

---

# Dependency Inversion Principle (DIP)

### Definition

> High-level modules should not depend on low-level modules.  
> Both should depend on abstractions.  
> Abstractions should not depend on details.  
> Details should depend on abstractions.

### In simple English

In simple English: Your business logic (high-level) shouldn’t directly depend on concrete classes (low-level). Instead, both should depend on interfaces (abstractions).

Suppose your code flows like this:

API -> Controller Layer -> Service Layer -> Repository Layer
 - In the Controller Layer, you accept the request from the API.
 - In the Service Layer, you pass the API arguments and do computation and all business logic.
 - In Repository Layer, you interact with databases or external service to persist or get data.

Suppose we are building a Ticketing booking system. Now, we will write code without following DIP.

---

### ❌ Violating DIP

```cpp
#include <iostream>
using namespace std;

class TicketRepository {
public:
    string bookTicket(string userId, string movieId) {
        cout << "Saving booking in DB for user "
             << userId << " and movie " << movieId << endl;
        return "booking-id-123";
    }
};

class BookTicketService {
private:
    TicketRepository repo; // tightly coupled

public:
    string execute(string userId, string movieId) {
        return repo.bookTicket(userId, movieId);
    }
};
```

### Problems

- Cannot switch DB easily
- Tight coupling
- Violates OCP
- Hard to test

---

## ✅ Applying DIP

### Step 1 — Create Abstraction

```cpp
class ITicketRepository {
public:
    virtual string bookTicket(string userId, string movieId) = 0;
    virtual ~ITicketRepository() {}
};
```

### Step 2 — Implement Concrete Class

```cpp
class TicketRepository : public ITicketRepository {
public:
    string bookTicket(string userId, string movieId) override {
        cout << "Saving booking in DB for user "
             << userId << " and movie " << movieId << endl;
        return "booking-id-123";
    }
};
```

### Step 3 — Inject Dependency

```cpp
class BookTicketService {
private:
    ITicketRepository& repo;

public:
    BookTicketService(ITicketRepository& r) : repo(r) {}

    string execute(string userId, string movieId) {
        return repo.bookTicket(userId, movieId);
    }
};
```

### Wiring Everything

```cpp
int main() {
    TicketRepository repo;
    BookTicketService service(repo);

    string bookingId = service.execute("u1", "m101");
    cout << bookingId << endl;
}
```

Now:

- High-level module depends on abstraction
- Concrete repository depends on abstraction
- Switching DB = create new class implementing `ITicketRepository`

NOTE: You may be observing that BookTicketService depends on the interface of the Repository instead of a concrete class. But BookTicketController directly depend upon the class BookTicketService instead of the interface.
Well, making the interface of the Service layer may or may not be worth it. Because the implementation of the Repo layer may change, like changing MySQL to MongoDB, but if you are changing the service layer, then you should write a new API altogether instead of changing the implementation of the service layer.

That’s DIP.

---

And with that, your SOLID principles are complete.