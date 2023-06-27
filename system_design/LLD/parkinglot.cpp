#include<bits/stdc++.h>

using namespace std;

class vehicle {
    public:
        int vehicle_id;
        string vehicleType;
};

class parkingSpot {
    public:
        int id;
        bool isEmpty;
        vehicle* vehicle;
        int price;
        void parkVehicle(vehicle* pVehicle) {
            isEmpty = false;
            vehicle = pVehicle;
        }
        void removeVehicle(vehicle* pVehicle) {
            isEmpty = true;
            vehicle = nullptr;
        }
};

class twoWheelerSpot: public parkingSpot {
    public:
        twoWheelerSpot() {
            this->price = 30;
        }
};

class twoWheelerSpot: public parkingSpot {
    public:
        twoWheelerSpot() {
            this->price = 50;
        }
};


class parkingLotManager {
    public:
        virtual parkingSpot* findParkingSpace() = 0;
        virtual void addParkingSpace(parkingSpot* pParkingSpot) = 0;
        virtual void removeParkingSpot(parkingSpot* pParkingSpot) = 0;
        virtual void parkVehicle(vehicle* vehicle) = 0;
        virtual void removeVehicle(parkingSpot* pParkingSpot) = 0;
        virtual void setStrategy(parkingStrategy* pStrategy) = 0;
};

class twoWheelerParkingLotManager: public parkingLotManager {
    public:
        list<twoWheelerSpot*> twoWheelerSpots;
    //all the function to be implemented
        void setStrategy(parkingStrategy* pStrategy) {
            strategy_ = pStrategy;
        }
    private:
        parkingStrategy* strategy_;
};

class fourWheelerParkingLotManager: public parkingLotManager {
    public:
        list<twoWheelerSpot*> fourWheelerSpots;
    //all the function to be implemented
        void setStrategy(parkingStrategy* pStrategy) {
            strategy_ = pStrategy;
        }
    private:
        parkingStrategy* strategy_;
};

class parkingStrategy {
    public:
        virtual void findSpace() = 0;
};

class nearestEntranceStrategy: public parkingStrategy {
    void findSpace() {
        cout<<"Nearest space to Entrance allocated\n";
    }
};

class nearestExitStrategy: public parkingStrategy {
    void findSpace() {
        cout<<"Nearest space to Exit allocated\n";
    }
};

class ticket {
    public:
        string entryTime;
        vehicle* Vehicle;
        parkingSpot* ParkingSpot;
        ticket(string pEntryTime, vehicle* pVehicle, parkingSpot* pParkignSpot) :entryTime(pEntryTime), Vehicle(pVehicle), ParkingSpot(pParkingSpot) {}
        ticket() {}
        ticket* getTicket() {
            return new ticket(entryTime, Vehicle, ParkingSpot);
        }
};

class parkingSpotFactory {
    public:
        static parkingLotManager* getParkingSpotManager(string vehicleType) {
            if(vehicleType=="two wheeler")
                return new twoWheelerParkingLotManager;
            else if (vehicleType == "four wheeler")
                return new fourWheelerParkingLotManager;
            else
                return new fourWheelerParkingLotManager;
        } 
};

class entrance {
    public:
        parkingLotManager* Manager;
    entrance(vehicle* pVehicle, string strategy) {
        this->Manager = parkingSpotFactory::getParkingSpotManager(pVehicle->vehicleType);
    }
};


int main() {
    return 0;
}