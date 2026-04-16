/*
Link: https://refactoring.guru/design-patterns/strategy


Same Routing / Navigation problem
*/


#include<bits/stdc++.h>

using namespace std;

//Strategy interface
class IRountingStrategy {
    public:
        virtual ~IRountingStrategy() {}
        virtual void findRoute() = 0;
};

//context class
class Navigator {
    private:
        IRountingStrategy* strategy;
    public:
        void setStrategy(IRountingStrategy* _strategy) {
            this->strategy = _strategy;
            cout<<"New routing strategy set"<<endl;
        }

        void navigate(string a, string b) {
            this->strategy->findRoute();
            cout<<"Navigation from "<<a<<" to "<<b<<endl;
        }
};


class WalkStrategy : public IRountingStrategy {
    public:
        void findRoute() override {
            cout<<"Found the shortest walking path "<<endl;
        }
};

class BikeStrategy : public IRountingStrategy {
    public:
        void findRoute() override {
            cout<<"Found the shortest 2 wheeler path "<<endl;
        }
};

class DriveStrategy : public IRountingStrategy {
    public:
        void findRoute() override {
            cout<<"Found the shortest 4 wheeler path "<<endl;
        }
};

int main() {
    Navigator* nav = new Navigator();
    cout<<"Walking path: ";
    nav->setStrategy(new WalkStrategy());
    nav->navigate("IIT Delhi", "Nakhas police Chowk");
    cout<<"Bike path: ";
    nav->setStrategy(new BikeStrategy());
    nav->navigate("IIT Delhi", "Nakhas police Chowk");
    cout<<"Drive path: ";
    nav->setStrategy(new DriveStrategy());
    nav->navigate("IIT Delhi", "Nakhas police Chowk");

    delete nav;
    return 0;
}