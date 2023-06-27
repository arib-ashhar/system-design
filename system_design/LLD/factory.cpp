/*
Link: https://sourcemaking.com/design_patterns/factory_method
Link: https://www.youtube.com/watch?v=tv54FY48Vio&list=PLliXPok7ZonlZJuAN0hvUnf5ovFepjxU0&index=2&pp=iAQB

*/


#include<bits/stdc++.h>

using namespace std;

class vehicle {
    public:
    virtual void getVehicle() = 0;
};

class car: public vehicle {
    public:
    void getVehicle() {
        cout<<"New Car manufactured\n";
    }
};

class truck: public vehicle {
    public:
    void getVehicle() {
        cout<<"New Truck Manufactured\n";
    }
};

class vehicleFactory {
    public:
    static vehicle* createVehicle(string vehicleType);
};

vehicle* vehicleFactory::createVehicle(string vehicleType) {
    if(vehicleType == "Car")
        return new car;
    else if(vehicleType == "Truck")
        return new truck;
    else
        return new car;
}


int main() {
    string input;
    cout<<"Enter vehicle type: ";
    cin>>input;
    vehicle* vhicle_object = vehicleFactory::createVehicle(input);
    vhicle_object->getVehicle();
    return 0;
}