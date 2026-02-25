/*
Link: https://refactoring.guru/design-patterns/factory-method
Link: https://www.youtube.com/watch?v=tv54FY48Vio&list=PLliXPok7ZonlZJuAN0hvUnf5ovFepjxU0&index=2&pp=iAQB

Same Logistics problem.

*/


#include<bits/stdc++.h>

using namespace std;

// This is the product interface
class Transport {
    public:
        virtual ~Transport() {}
        virtual bool doShipping() = 0;
};

class Truck : public Transport {
    public:
    Truck() {
        cout<<"Transport Object of type Truck created"<<endl;
    }

    bool doShipping() override {
        cout<<"Shipping done via land"<<endl;
        return true;
    }
};

class Ship : public Transport {
    public:
    Ship() {
        cout<<"Transport Object of type Ship created"<<endl;
    }

    bool doShipping() override {
        cout<<"Shipping done via water"<<endl;
        return true;
    }
};

// creator class
class Logistics {
    public:
        virtual ~Logistics() {};
        virtual Transport* createTransport() = 0;

        bool planDelivery() {
            Transport* transport = this->createTransport();
            transport->doShipping();
            delete transport;
            return true;
        }
};

class LandLogistics: public Logistics {
    public:
        Transport* createTransport() override {
            cout<<"Land Logistics is triggered"<<endl;
            return new Truck();
        }
};

class SeaLogistics : public Logistics {
    public:
        Transport* createTransport() override {
            cout<<"Sea Logistics is triggered"<<endl;
            return new Ship();
        }
};

//client code
void manageLogistics(string input) {
    if(input == "L") {
        Logistics* logistics = new LandLogistics();
        logistics->planDelivery();
    }
    else if(input == "S") {
        Logistics* logistics = new SeaLogistics();
        logistics->planDelivery();
    }
}

int main() {
    string input;
    cout<<"Enter Logistics Type (L/S): ";
    cin>>input;
    manageLogistics(input);
    return 0;
}