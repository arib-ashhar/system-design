#include<bits/stdc++.h>

using namespace std;



enum BOOKING_STATUS {
    CREATED,
    CONFIRMED,
    EXPIRED
};

enum SEAT_CATEGORY {
    PREMIUM,
    RECLINER,
    NORMAL
};

// Payment

class PaymentStrategy {
    public:
        virtual bool processPayment() = 0;
};

class UPIPayment : public PaymentStrategy {
    public:
        bool processPayment() override {
            cout<<"UPI Paymnt processed"<<endl;
            return true;
        }
};


class PaymentService {
    private:
        PaymentStrategy* paymentStrategy;
        BookingService* bookingService;
        unordered_map<string, int> failedBookings;
    public:
        PaymentService(PaymentStrategy* paymentStrategy, BookingService* bookingService) {
            this->paymentStrategy = paymentStrategy;
            this->bookingService = bookingService;
        }

        bool processPaymentRequest(string bookingId, User user) {
            bool result = paymentStrategy->processPayment();
            if(!result) {
                processFailedPayment(bookingId, user);
                return false;
            }
            return true;
        }

        bool processFailedPayment(string bookingId, User user) {
            Booking* booking = bookingService->getBooking(bookingId);
            if(booking.getUser().Id != user.Id) {
                cout<<"Only booking owner can process failure"<<endl;
                return false;
            }

            failedBookings[bookingId]++;
            // If lets say 5 failed booking can reject the request and save it in the DB.
            return true;
        }
};

class PaymentController {
    private:
        PaymentService* paymentService;
    public:
        PaymentController(PaymentService* paymentService) {
            this->paymentService = paymentService;
        }
        void processPayment(string bookingId, User user) {
            paymentService->processPayment(bookingId, user);
        }

};



class Theatre {
    private:
        int id;
        string name;
        vector<Screen*> screens;
    public:
        Theatre(int id, string name) {
            this->id = id;
            this->name = name;
        }

        void addScreen(Screen* screen) {
            screens.push_back(screen);
        }

        vector<Screen*> getScreens() {
            return this->screens;
        }

        // getter, setters
};

class Screen {
    private:
        int id;
        string name;
        Theatre* theatre;
        vector<Seats*> seats;
    
    public:
        Screen(int id, string name, Theatre* theatre) {
            this->id = id;
            this->name = name;
            this->theatre = theatre;
        }

        void addSeat(Seat* seat) {
            seats.push_back(seat);
        }

        // Getters and Setters Section Start
	    int getScreenId() {
	        return id;
	    }
	    vector<Seat*> getSeats() {
	        return seats;
	    }
	    Theatre* getTheatre() {
	        return theatre;
	    }
};

class Show {
    private:
        int id;
        Date showTime;
        int durationInMinutes;
        Movie* movie;
        Screen* screen;
    public:
        Show(int id, Movie* movie, Screen* screen, Date showTime, int durationInMinutes) {
            id = id;
            showTime = showTime;
            movie = movie;
            durationInMinutes = durationInMinutes;
            screen = screen;
        }

        // Getters Section Start
	    int getId() {
	        return id;
	    }
	    Movie* getMovie() { return movie;}
	    Screen* getScreen() {
	        return screen;
	    }
	    Date getStartTime() {
	        return startTime;
	    }
	    int getdurationInMinutes() {
	        return durationInMinutes;
	    }
};

class Seat {
    private:
        int id;
        int row;
        SEAT_CATEGORY seatCategory;
    public:
        Seat(int id, int row, SEAT_CATEGORY seatCategory) {
            this->id = id;
            this->row = row;
            this->seatCategory = seatCategory;
        }

        //getters / setters
        int getSeatId() {
            return id;
        }
        int getSeatRow() {
            return row;
        }
        int getSeatCategory() {
            return seatCategory;
        }
};

class Movie {
    private:
        int id;
        string name;
        string description;
    Movie(int id, int name, int description) {
        id = id;
        name = name;
        description = description;
    }

    // getters
};

class User {
    private:
	    string name;
	    string emailAddress;
	public:
	    User(String name, string emailAddress) {
	        this.name = name;
	        this.emailAddress = emailAddress;
	    }
	    // Getters Section Start
	    string getUserName() {
	        return name;
	    }
	    string getUserEmail() {
	        return emailAddress;
	    }
};


class Booking {
    private:
        string id;
        Show* show,
        vector<Seat*> bookedSeats;
        User* user,
        int bookingStatus;
    public:
        Booking(string id, Show* show, User* user, vector<Seat*>& bookedSeats) {
            this->id = id;
            this->show = show;
            this->bookedSeats = bookedSeats;
            this->user = user;
            this->bookedStatus = BOOKING_STATUS.CREATED;
        }

        string getId() {
            return id;
        }

        bool isConfirmed() {
            return bookedStatus == BOOKING_STATUS.CONFIRMED;
        }

        void confirmBooking() {
            if(bookedStatus != BOOKING_STATUS.CREATED)
                cout<<"Canont confirm booking which is not created"<<endl;
            return;
            this->bookedStatus = BOOKING_STATUS.CONFIRMED;
        }

        void expireBooking() {
            if(bookedStatus != BOOKING_STATUS.CREATED)
                cout<<"Canot expire booking which is not created"<<endl;
            this->bookedStatus = BOOKING_STATUS.EXPIRED;
        }

        Show* getShow() {
            return show;
        }

        vector<Seats*> getSeatsBooked() {
            return bookedSeats;
        }

        User* getUser() {
            return user;
        }

        BOOKING_STATUS getBookingStatus() {
            return bookedStatus;
        }
};


class SeatLock {
    private:
        Seat* seat;
        Show* show;
        User* lockedBy;
        Date lockTime;
        int lockoutInSeconds;
    public:
        SeatLock(Seat* seat, Show* show, User* lockedBy, int lockoutInSeconds, Date lockTime) {
            seat = seat;
            show = show;
            lockedBy = lockedBy;
            lockoutInSeconds = lockoutInSeconds;
            lockTime = lockTime;
        }

        bool isLockExpired() {
            auto now = chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(now - lockTime).count();
            return duration > lockoutInSeconds;
        }

        Seat* getSeat() {
            return seat;
        }

        void setSeat(Seat* seat) {
            this->seat = seat;
        }

        Show* getShow() {
            return show;
        }

        void setShow(Show* show) {
            this->show = show;
        }

        User* getLockedBy() {
            return user;
        }

        void setUser(User* user) {
            this->user = user;
        }

        int getLockoutInSeconds() {
            return timeoutInSeconds;
        }

        void setLockoutInSeconds(int lockoutInSeconds) {
            this->lockoutInSeconds = lockoutInSeconds;
        }

        Date getLockTime() {
            return lockTime;
        }

        void setLockTime(Date lockTime) {
            this->lockTime = lockTime;
        }
};


class ISeatLockProvider {
    public:
        virtual void lockSeats(Show* show, vector<Seat*> seats, User* user) = 0;
        virtual void unlockSeats(Show* show, vector<Seat*> seats, User* user) = 0;
        bool validateLock(Show* show, Seat* seat, User* user);
	    vector<Seat*> getLockedSeats(Show* show) = 0;
};


class SeatLockProvider : public ISeatLockProvider {
    private:
        int lockoutTime;
        unordered_map<int, unordered_map<int, SeatLock*>> locks;
        mutex mtx;

        bool isSeatLocked(Show* show, Seat* seat) {
            if(locks.find(show->id) == locks.end()) return false;
            auto& showLocks = locks[show->id];
            if(showLocks.find(seat->id) == showLocks.end()) return false;
            return true;
        }

        SeatLock* getSeatLock(Show* show, Seat* seat) {
            auto& showLocks = locks[show->id];
            return showLocks[seat->id];
        }
    public:
        SeatLockProvider(int lockoutTime) {
            this->lockoutTime = lockoutTime;
        }

        bool lockSeats(Show* show, vector<Seat*> seats, User* user) override {
            lock_guard<mutex> guard(mtx); // Thread safety

            for (const auto& seat : seats) {
                if (!isSeatLocked(show, seat)) {
                    SeatLock* existingLock = getSeatLock(show, seat);
                    if(!existingLock->isLockExpired()) {
                        cout<<"Seat is already Loacked"<<endl;
                        return false;
                    }
                } else {
                    cout<<"One of the seats is already loacked"<<endl;
                    return false;
                }
            }

            // Step 2: Acquire locks
            for (const auto& seat : seats) {
                locks[show->id][seat->id] = new SeatLock(seat, show, user, lockoutTime, chrono::steady_clock::now());
            }
            return true;
        }

        void unlockSeats(Show* show, vector<Seat*> seats, User* user) override {
            lock_guard<mutex> guard(mtx);
            if(locks.find(show->id) == locks.end())
                return;
            for(Seat* seat: seats) {
                if(isSeatLocked(show, seat)) {
                    auto& seatLock = getSeatLock(show, seat);
                    if(seatLock.getLockedBy() == user) {
                        locks[show->id].erase(seat->id);
                    }
                }
            }
            return;
        }

        bool validateSeat(Show* show, Seat* seat, User* user) override {
            if(isSeatLocked(show, seat)) {
                SeatLock* seatLock = getSeatLock(show, seat);
                if(!seatLock.isLockExpired() && seatLock.getLockedBy() == user)
                    return true;
            }
            return false;
        }

        vector<SeatLock*> getSeatLocks(Show* show) override {
            vector<SeatLock*> seatLocks;
            if(locks.find(show->id) != locks.end()) {
                for(auto& [seatId, seatLock] : locks[show->id])
                    seatLocks.push_back(seatLock);
            }
            return seatLocks;
        }

};


class MovieService {
    private:
        unordered_map<int, Movie*> movies;
        atomic<int> movieCounter;
    public:
        MovieService() {
            this->movieCounter = 0;
        }

        Movie* getMovie(int movieId) {
            if(movies.find(movieId) != movies.end())
                return movies[movieId];
            else {
                cout<<"Movie does not exist"<<endl;
                return nullptr;
            }
        }

        Movie* createMovie(string name, string description) {
            Movie* movie = new Movie(this->movieCounter, name, description);
            movies[this->movieCounter] = movie;
            this->movieCounter++;
            return movie;
        }
};

class TheatreService {
    private:
        unordered_map<int, Theatre*> theatres;
        unordered_map<int, Screen*> screens;
        unordered_map<int, Seat*> seats;

        // Atomic counters for thread-safe unique ID generation
        atomic<int> theatreCounter{0};
        atomic<int> screenCounter{0};
        atomic<int> seatCounter{0};

    public:

        Seat* getSeat(int seatId) {
            if (seats.find(seatId) == seats.end()) {
                throw runtime_error("Seat with ID " + to_string(seatId) + " not found.");
            }
            return seats[seatId];
        }

        Theatre* getTheatre(int theatreId) {
            if (theatres.find(theatreId) == theatres.end()) {
                throw runtime_error("Theatre with ID " + to_string(theatreId) + " not found.");
            }
            return theatres[theatreId];
        }

        Screen* getScreen(int screenId) {
            if (screens.find(screenId) == screens.end()) {
                throw runtime_error("Screen with ID " + to_string(screenId) + " not found.");
            }
            return screens[screenId];
        }

        Theatre* createTheatre(const string& theatreName) {
            int id = ++theatreCounter;
            auto theatre = make_shared<Theatre>(id, theatreName);
            theatres[id] = theatre;
            return theatre;
        }

        Screen* createScreenInTheatre(const string& screenName, Theatre* theatre) {
            int id = ++screenCounter;
            auto screen = make_shared<Screen>(id, screenName, theatre.get());
            screens[id] = screen;
            theatre->addScreen(screen.get());
            return screen;
        }

        Seat* createSeatInScreen(int rowNo, SEAT_CATEGORY category, Screen* screen) {
            int id = ++seatCounter;
            auto seat = make_shared<Seat>(id, rowNo, category);
            seats[id] = seat;
            screen->addSeat(seat.get());
            return seat;
        }
};



class ShowService {
    private:
        unordered_map<int, Show*> shows;
        atomic<int> showCounter{0};
    
    public:
        ShowService() {}

        Show* getShowById(int id) {
            if(show.find(id) != shows.end())
                return shows[id];
            throw runtime_error("Show with ID " + to_string(id) + " not found.");
        }

        Show* createShow(Movie* movie, Screen* screen, int durationInMinutes, Date showTime) {
            int showId = ++showCounter;
            Show* show = new Show(showId, showTime, durationInMinutes, movie, screen);
            shows[showId] = show;
            return show;
        }

        vector<Show*> getShowsForScreen(Screen* screen) {
            vector<Show*> result;
            for(auto& show:shows) {
                if(show.getScreen().getId() == screen.getId())
                    result.push_back(show);
            }
            return result;
        }
};

class SeatAvailabilityService {
    private:
        BookingService* bookingService;
        ISeatLockProvider* seatLockProvider;
    public:
        SeatAvailabilityService(BookingService* bookingService, ISeatLockProvider* seatLockProvider) {
            this->bookingService = bookingService;
            this->seatLockProvider = seatLockProvider;
        }

        vector<Seat*> getAvailableSeats(Show* show) {
            vector<Seat*> allSeats = show->getScreen()->getSeats();
            vector<Seat*> bookedSeats = bookingService->getBookedSeats(show);
            vector<SeatLock*> lockedSeatLocks = seatLockProvider->getSeatLocks(show);
            vector<Seat*> lockedSeats;
            for(auto& lock : lockedSeatLocks)
                lockedSeats.push_back(lock->getSeat());

            vector<Seat*> availableSeats;

            for(auto& seat : allSeats) {
                if(find(bookedSeats.begin(), bookedSeats.end(), seat) == bookedSeats.end() &&
                    find(lockedSeats.begin(), lockedSeats.end(), seat) == lockedSeats.end())
                    availableSeats.push_back(seat);
            }
            return availableSeats;
        }
};


class BookingService {
    private:
        unordered_map<string, Booking*> bookings;
        ISeatLockProvider* seatLockProvider;
        atomic<int> bookingCounter{0};
        std::mutex mapMutex;
    public:
        BookingService(ISeatLockProvider* seatLockProvider) {
            this->seatLockProvider = seatLockProvider;
        }

        Booking* getBookingById(string id) {
            std::lock_guard<std::mutex> lock(mapMutex);
            if(bookings.find(id) != bookings.end())
                bookings[id];
            throw runtime_error("Booking with " + id + "does not exist");
        }

        vector<Booking*> getAllBookingByShow(Show* show) {
            vector<Booking*> result;
            std::lock_guard<std::mutex> lock(mapMutex);
            for(auto& [id, booking] : bookings) {
                if(booking.getShow().getId() == show.getId())
                    result.push_back(booking);
            }
            return result;
        }

        Booking* createBooking(User* user, Show* show, vector<Seat*> seats) {
            if(isAnySeatAlreadyBooked(show, seats))
                throw runtime_error("Some of the seats are already booked");
            seatLockProvider->lockSeats(show, seats, user);
            string bookingId = to_string(++bookingCounter);

            Booking* booking = new Booking(bookingId, show, user, seats);
            {
                std::lock_guard<mutex> lock(mapMutex);
                bookings[bookingId] = booking;
            }
            return booking;
        }

        void confirmBooking(Booking* booking, User* user) {
            if(booking->getUser().getId() != user.getId())
                throw runtime_error("ONly user who booked can confirm");
            for(auto& seat: booking->getSeatsBooked()) {
                if(!seatLockProvider.validateLock(booking->getShow(), seat, user))
                    throw runtime_error("Acquired seats are already booked or session expired");
            }
            booking->confirmBooking();
        }
        
        vector<Seat*> getBookedSeats(Show* show) {
            vector<Seat*> bookedSeats;
            auto allBookings = getAllBookingByShow(show);

            for (const auto& booking : allBookings) {
                if (booking->isConfirmed()) {
                    auto seats = booking->getSeatsBooked();
                    bookedSeats.insert(bookedSeats.end(), seats.begin(), seats.end());
                }
            }
            return bookedSeats;
        }
        
    private:
        bool isAnySeatAlreadyBooked(Show* show, vector<Seat*>& seats) {
            auto alreadyBooked = getBookedSeats(show);
            
            for (const auto& seat : seats) {
                if (find(alreadyBooked.begin(), alreadyBooked.end(), seat) != alreadyBooked.end()) {
                    return true;
                }
            }
            return false;
        }
};

class MovieController {
    private:
        MovieService* movieService;
    public:
        MovieController(MovieService* movieService) {
            this->movieService = movieService;
        }

        Movie* createMovie(string name, string description) {
            return movieService->createMovie(name, description);
        }

        Movie* getMovie(int movieId) {
            return movieService->getMovie(movieId);
        }
};


class ScreenController {
    private:
        TheatreService* theatreService;
    public:
        ScreenController(TheatreService* theatreService) {
            this->theatreService = theatreService;
        }

        Screen* createScreenInTheatre(string screenName, Theatre* theatre) {
            return theatreService->createScreenInTheatre(screenName, theatre);
        }

        Screen* getScreen(int screenId) {
            return theatreService->getScreen(screenId);
        }

        Seat* createSeatInScreen(int rowNo, SEAT_CATEGORY category, Screen* screen) {
            return theatreService->createSeatInScreen(rowNo, category, screen);
        }
};


class TheatreController {
    private:
        TheatreService* theatreService;
    public:
        TheatreController(TheatreService* theatreService) {
            this->theatreService = theatreService;
        }

        Theatre* createTheatre(string theatreName) {
            return theatreService->createTheatre(theatreName);
        }

        Theatre* getTheatre(int theatreId) {
            return theatreService->getTheatre(theatreId);
        }
};

int main() {
    // Services
    MovieService* movieService = new MovieService();
    TheatreService* theatreService = new TheatreService();

    // Controllers
    MovieController* movieController = new MovieController(movieService);
    TheatreController* theatreController = new TheatreController(theatreService);
    ScreenController* screenController = new ScreenController(theatreService);

    // Step 1: Create movie
    Movie* avengers = movieController->createMovie("Avengers: Endgame", "Marvel movie");

    // Step 2: Create theatre
    Theatre* inox = theatreController->createTheatre("INOX Noida");

    // Step 3: Create screen inside theatre
    Screen* screen1 = screenController->createScreenInTheatre("Audi 1", inox);

    // Step 4: Add seats in screen
    Seat* seat1 = screenController->createSeatInScreen(1, SEAT_CATEGORY::PREMIUM, screen1);
    Seat* seat2 = screenController->createSeatInScreen(1, SEAT_CATEGORY::PREMIUM, screen1);
    Seat* seat3 = screenController->createSeatInScreen(2, SEAT_CATEGORY::NORMAL, screen1);

    cout<<"Movie created for simulation"<<endl;
    cout<<"Theatre and screen created for simulation"<<endl;
    cout<<"Seats added in screen: "
        <<seat1->getSeatId()<<" "
        <<seat2->getSeatId()<<" "
        <<seat3->getSeatId()<<endl;

    cout<<endl;
    cout<<"Starting concurrent booking simulation"<<endl;

    User* user1 = new User("Aryan", "aryan@gmail.com");
    User* user2 = new User("Rahul", "rahul@gmail.com");

    vector<int> requestedSeats = {seat1->getSeatId(), seat2->getSeatId()};
    unordered_set<int> bookedSeatsForShow;
    mutex bookingMutex;

    auto simulateBooking = [&](User* user, string userLabel) {
        cout<<userLabel<<" is trying to book seats ";
        for(auto& seatId : requestedSeats) {
            cout<<seatId<<" ";
        }
        cout<<endl;

        this_thread::sleep_for(chrono::milliseconds(100));

        lock_guard<mutex> lock(bookingMutex);

        bool canBook = true;
        for(auto& seatId : requestedSeats) {
            if(bookedSeatsForShow.find(seatId) != bookedSeatsForShow.end()) {
                canBook = false;
                break;
            }
        }

        if(!canBook) {
            cout<<userLabel<<" booking failed because seat is already booked"<<endl;
            return;
        }

        for(auto& seatId : requestedSeats) {
            bookedSeatsForShow.insert(seatId);
        }
        cout<<userLabel<<" booking confirmed"<<endl;
    };

    thread t1(simulateBooking, user1, "User1");
    thread t2(simulateBooking, user2, "User2");

    t1.join();
    t2.join();

    cout<<"Final booked seats are: ";
    for(auto& seatId : bookedSeatsForShow) {
        cout<<seatId<<" ";
    }
    cout<<endl;

    delete movieController;
    delete theatreController;
    delete screenController;
    delete user1;
    delete user2;
    delete movieService;
    delete theatreService;

    return 0;
}
