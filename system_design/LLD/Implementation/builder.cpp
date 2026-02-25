/*
Link: https://refactoring.guru/design-patterns/builder


Same House example
*/


#include<bits/stdc++.h>

using namespace std;

//products interface
class House {
    public:
        string doorsAndWindows;
        string roof;
        string walls;
    
        House() {
            cout<<"Created House object"<<endl;
        }
        virtual ~House() {}

        virtual string getDoorsAndWindows() = 0;

        virtual string getWalls() = 0;

        virtual string getRoof() = 0;

        virtual void setDoorsAndWindows() = 0;

        virtual void setRoof() = 0;

        virtual void setWalls() = 0;
};

// Builder Interface
class Builder {
    public:
        virtual ~Builder() {}
        virtual void buildWalls() = 0;
        virtual void buildDoorsAndWindows() = 0;
        virtual void buildRoof() = 0;
        virtual House* getResult() = 0;
        virtual void reset() = 0;
};

class IndianHouse : public House {
    public:
    
        IndianHouse() {
            cout<<"Created Indian House"<<endl;
        }
        ~IndianHouse() {}

        string getDoorsAndWindows() override {
            return this->doorsAndWindows;
        }

        string getWalls() override {
            return this->walls;
        }

        string getRoof() override {
            return this->roof;
        }

        void setDoorsAndWindows() override {
            this->doorsAndWindows = "Iron doorsAndWindows";
            cout<<"Created "<<this->doorsAndWindows<<endl;
        }

        void setRoof() override {
            this->roof = "Concrete roof";
            cout<<"Created "<<this->roof<<endl;
        }

        void setWalls() override {
            this->walls = "Concrete walls";
            cout<<"Created "<<this->walls<<endl;
        }
};

class AmericanHouse : public House {
    public:
    
        AmericanHouse() {
            cout<<"Created American House"<<endl;
        }
        ~AmericanHouse() {}

        string getDoorsAndWindows() override {
            return this->doorsAndWindows;
        }

        string getWalls() override {
            return this->walls;
        }

        string getRoof() override {
            return this->roof;
        }

        void setDoorsAndWindows() override {
            this->doorsAndWindows = "Wooden doorsAndWindows";
            cout<<"Created "<<this->doorsAndWindows<<endl;
        }

        void setRoof() override {
            this->roof = "snow roof";
            cout<<"Created "<<this->roof<<endl;
        }

        void setWalls() override {
            this->walls = "Wooden walls";
            cout<<"Created "<<this->walls<<endl;
        }
};

class IndianHouseBuilder : public Builder {
    private:
        IndianHouse* house;
    public: 
        IndianHouseBuilder() {
            cout<<"Indian House Builder triggered\n";
            this->house = new IndianHouse();
        }
        void buildWalls() override {
            this->house->setWalls();
        }
        void buildDoorsAndWindows() override {
            this->house->setDoorsAndWindows();
        }
        void buildRoof() override {
            this->house->setRoof();
        }
        House* getResult() override {
            return this->house;
        }
        void reset() override {
            delete house;
            this->house = new IndianHouse();
        }
    
};

class AmericanHouseBuilder : public Builder {
    private:
        AmericanHouse* house;
    public: 
        AmericanHouseBuilder() {
            cout<<"American House Builder triggered\n";
            this->house = new AmericanHouse();
        }
        void buildWalls() override {
            this->house->setWalls();
        }
        void buildDoorsAndWindows() override {
            this->house->setDoorsAndWindows();
        }
        void buildRoof() override {
            this->house->setRoof();
        }
        House* getResult() override {
            return this->house;
        }
        void reset() override {
            delete house;
            this->house = new AmericanHouse();
        }
    
};

//Director
class Director {
    public:
        Builder* builder;
        Director(Builder* builder) {
            this->builder = builder;
        }
        ~Director() {}
        void resetBuilder() {
            delete builder;
            this->builder = nullptr;
        }
        House* constructHouse() {
            this->builder->buildWalls();
            this->builder->buildDoorsAndWindows();
            this->builder->buildRoof();
            return this->builder->getResult();
        }
};


int main() {
    string region;
    cout<<"Enter Region (India(I) / America(A)): ";
    cin>>region;
    Director* director;
    if(region=="I") {
        director = new Director(new IndianHouseBuilder());
    }
    else {
        director = new Director(new AmericanHouseBuilder());
    }
    auto house = director->constructHouse();
    return 0;
}