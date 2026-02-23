# C++ OOP Concepts Notes

---

# By default all members of a class are private.

---

# Class, Members and Objects

## Access Specifiers

Access specifiers are used to control the accessibility of member variables.

- **private**: means only the member functions and friendly function can access these variables.  
- **public**: means any object of this class can be accessed by outside objects.  
- **protected**: means it can be accessed by sub class members also whcich is not in the case of private.  

---

## Class object can also be initialized like struct

```cpp
class base {
    public:
    int a;
};

int main(){
    //code here
    base obj={10};
    cout<<obj.a<<endl;
}
```

---

## Nested Class

```cpp
class Outer
{
  public:
    // Nested class inside Outer
    class Inner
    {
      public:
        void display()
        {
            cout << "This is the Inner class" << endl;
        }
    };

    void show()
    {
        cout << "This is the Outer class" << endl;
    }
};

int main()
{
    // Creating object of Outer class
    Outer outerObj;
    outerObj.show();

    // Creating object of Inner class using Outer
    Outer::Inner innerObj;
    innerObj.display();

    return 0;
}
```

**OUtPUT:**
```
0
```

**Links:**
- https://www.geeksforgeeks.org/c-classes-and-objects/
- https://www.geeksforgeeks.org/access-modifiers-in-c/

---

# Constructors

By default empty body constructor is constructed, and copy constructor as well and assignment operator also.

## Types of constructors
- Default Constructor  
- Parameterized Constructor  
- Copy Constructor  
- Move Constructor  

```cpp
class A {
public:
    int val;
  
    // Constructor without any parameters
    A() {
        cout << "Constructor called" << endl;
    }

    // Parameterized Constructor
    A(int x) {
        val = x;
    }

    // Copy constructor
    A(A& a) {
        val = a.val;
    }

    // Move Constructor
    A(int &&a) : val(move(a)) {
        cout << "Move constructor called!" << endl;
    }
};

int main() {
    A a1(20);
    
    // Creating another object from a1
    A a2(a1);   // Copy Constructor
    
    int a = 4;
    A a3(move(a));  // Move Constructor
    return 0;
}
```

**Link:**  
https://www.geeksforgeeks.org/constructors-c/

---

# Destructors

## When do we need to write a user-defined destructor?

- If we don’t write a destructor, the compiler provides a default one.  
- The default destructor works fine for classes without dynamic memory or pointers.  
- If a class has pointers or dynamically allocated memory, we must write a destructor.  
- A user-defined destructor releases memory or other resources before the object is destroyed.  
- Writing a destructor in such cases prevents memory leaks.  

**Link:**  
https://www.geeksforgeeks.org/destructors-c/

---

# Abstract Class

A class is abstract if it has at least one pure virtual function.  
A pure virtual function is a virtual function with no implementation in the base class, declared using `= 0`.  
A class with at least one pure virtual function is an abstract class that cannot be instantiated and serves as a blueprint for derived classes, which must provide their own implementation.

```cpp
class Shape {
public:
    virtual void draw() = 0; // Pure virtual function
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle\n";
    }
};
```

**Link:**  
https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/

---

# Template Class, Function

## Function Template

```cpp
template <typename T> 
T myMax(T x, T y){
    return (x > y) ? x : y;
}
```

## Class Template

```cpp
template <typename T> 
class Geek{
  public:
    T x;
    T y;

    // Constructor
    Geek(T val1, T val2) : x(val1), y(val2){
    }

    // Method to get values
    void getValues(){
        cout << x << " " << y;
    }
};
```

**Link:**  
https://www.geeksforgeeks.org/cpp/templates-cpp/

---

# this pointer

**Link:**  
https://www.geeksforgeeks.org/this-pointer-in-c/

---

# FRIEND FUNCTION

Friend functions/classes are used to access private or protected member of other classes in which it is declared as a friend.  
It can be a global function or function of another class.  
The keyword “friend” is placed only in the function declaration of the friend function and not in the function definition or call.  
Remember one thing, friendship is not mutual. If class A is a friend of B, then B doesn't become a friend of A automatically.

**Link:**  
https://www.geeksforgeeks.org/friend-class-function-cpp/

## Syntax:

```cpp
class base {
    private:
        int private_variable;
    protected:
        int protected_variable;
    
    //rest of the class definition

    friend int friendly_funcition(base&);
    friend class friendly_class;

    //or we can declare one member function of another class as friendly function using scope resolution operator
    friend int friendly_class::member_function(base&);
};

int friendly_funcition(base& object) {
    int x = object.private_variable;
    int y=object.protected_variable;
}

class friendly_class{
    public:
        int member_function(base& object) {
            int x=object.private_variable;
        }
};
```

---

# Encapsulation

Encapsulation is defined as binding together the data and the functions that manipulate them.  
Encapsulation is defined as wrapping up data and information under a single unit.

**Link:**  
https://www.geeksforgeeks.org/encapsulation-in-cpp/

---

# Abstraction

Abstraction means displaying only essential information and hiding the background details or implementation.  
It is done using classes and header files.  
Abstraction is mainly achieved using abstract classes and pure virtual functions.

```cpp
class Shape {
protected:
    string color;

public:
    Shape(string color) {
        this->color = color;
    }

    virtual double area() = 0;

    string getColor() {
        return color;
    }

    virtual ~Shape() {}
};

class Rectangle : public Shape {
    double length;
    double width;

public:
    Rectangle(string color, double length, double width)
        : Shape(color) {
        this->length = length;
        this->width = width;
    }

    double area() override {
        return length * width;
    }
};
```

---

## Interface in C++

In C++, a class can act as an interface if it contains only pure virtual functions and no data members or implemented methods.  
This enforces that all derived classes must implement every function, achieving full control abstraction.

```cpp
class Printable {
public:
    virtual void print() = 0;
    virtual void scan() = 0;

    virtual ~Printable() {}
};

class Document : public Printable {
public:
    void print() override {
        cout << "Printing document..." << endl;
    }
    void scan() override {
        cout << "Scanning document..." << endl;
    }
};

class Photo : public Printable {
public:
    void print() override {
        cout << "Printing photo..." << endl;
    }
    void scan() override {
        cout << "Scanning photo..." << endl;
    }
};
```

---

# Polymorphism

It basically means same function/operators can have multiple implementations/forms.

**Link:**  
https://www.geeksforgeeks.org/cpp-polymorphism/

```
            Polymorphism
            /            \
    compile time        Run time
    /           \               \
Function        operator        Virtual functions
Overloading     Overloading
```

---

# Function Overload (Compile Time)

When there are multiple functions with the same name but different parameters, then the functions are said to be overloaded.

Functions can be overloaded by changing the number of arguments or/and changing the type of arguments.

NOTE: different return type doesn't overload functions, it throws error for redifinition of same function.

```cpp
void add(int a, int b)
{
  cout << "sum = " << (a + b);
}
 
void add(double a, double b)
{
    cout << endl << "sum = " << (a + b);
}
 
int main()
{
    add(10, 2);
    add(5.3, 6.2);
    return 0;
}
```

**Link:**  
https://www.geeksforgeeks.org/function-overloading-c/

---

# Operator Overload (Compile Time)

In C++, we can make operators work for user-defined classes.

```cpp
class Complex {
private:
    int real, imag;
  
public:
    Complex(int r = 0, int i = 0)
    {
        real = r;
        imag = i;
    }
  
    Complex operator+(Complex const& obj)
    {
        Complex res;
        res.real = real + obj.real;
        res.imag = imag + obj.imag;
        return res;
    }
    void print() { cout << real << " + i" << imag << '\n'; }
};
  
int main()
{
    Complex c1(10, 5), c2(2, 4);
    Complex c3 = c1 + c2;
    c3.print();
}
```

**Link:**  
https://www.geeksforgeeks.org/operator-overloading-cpp/

---

# Function Overriding (Run Time Polymorphism)

Function signature should be same, i.e the return type and parameters should be same.

```cpp
class Parent {
public:
    void GeeksforGeeks()
    {
        cout << "Base Function" << endl;
    }
};
 
class Child : public Parent {
public:
    void GeeksforGeeks()
    {
        cout << "Derived Function" << endl;
    }
};
 
int main()
{
     Child Child_Derived;
     Child_Derived.GeeksforGeeks();
     Child_Derived.Parent::GeeksforGeeks();

     Parent* ptr = &Child_Derived;
     ptr->GeeksforGeeks();
     return 0;
}
```

**OUTPUT:**
```
Derived Function
Base Function
Base Function
```

---

# Virtual Function (Run Time Polymorphism)

A virtual function is a member function that is declared in the base class using the keyword `virtual` and is re-defined in the derived class.

## Without Virtual

```cpp
// Base class
class Shape {
public:
    Shape(int l, int w)
    {
        length = l;
        width = w;
    }
    int get_Area()
    {
        cout << "This is call to parent class area\n";
        return 1;
    }
protected:
    int length, width;
};
```

**OUTPUT:**
```
This is call to parent class area
This is call to parent class area
```

---

## With Virtual

```cpp
class Shape {
public:
    virtual void calculate()
    {
        cout << "Area of your Shape ";
    }

    virtual ~Shape()
    {
        cout << "Shape Destuctor Call\n";
    }
};
```

**Note:**  
In virtual function the actual function that is called depends on the type of the object calling it not the type of pointer.

---

# Inheritance

It is used to provide code reusability.

## Syntax

```cpp
class  <derived_class_name> : <access-specifier> <base_class_name>
{
        //body
}
```

## Types Of Inheritance

- Single inheritance  
- Multilevel inheritance  
- Multiple inheritance  
- Hierarchical inheritance  
- Hybrid inheritance  

---

# new and delete operator

It is used to dynamically allocate memory.

```cpp
int* ptr = new int;
int* arr_ptr = new int[10];
class_name* ptr = new class_name;

delete ptr;
delete[] arr_ptr;
```

**Link:**  
https://www.geeksforgeeks.org/new-and-delete-operators-in-cpp-for-dynamic-memory/