/*
Link: https://refactoring.guru/design-patterns/abstract-factory
Link: https://www.youtube.com/watch?v=17i8a-pUtx8&list=PLliXPok7ZonlZJuAN0hvUnf5ovFepjxU0&index=7

Same Furniture example
*/


#include<bits/stdc++.h>

using namespace std;

//Abstract Product-1
class Chair {
    public:
        virtual ~Chair() {}
        virtual bool hasLegs() = 0;
        virtual bool hasArms() = 0;
};

// concrete Products for Product-1
class ArtDecoChair : public Chair {
    public:
    ArtDecoChair() {
        cout<<"Chair of type ArtDeco created\n";
    }

    bool hasLegs() override {
        cout<<"ArtDeco has small legs\n";
        return true;
    }

    bool hasArms() override {
        cout<<"ArtDeco has Arms\n";
        return true;
    }
};

class VictorianChair : public Chair {
    public:
    VictorianChair() {
        cout<<"Chair of type Victorian created\n";
    }

    bool hasLegs() override {
        cout<<"Victorian has long legs\n";
        return true;
    }

    bool hasArms() override {
        cout<<"Victorian has Arms\n";
        return true;
    }
};

class ModernChair : public Chair {
    public:
    ModernChair() {
        cout<<"Chair of type Modern created\n";
    }

    bool hasLegs() override {
        cout<<"Modern has no legs\n";
        return false;
    }

    bool hasArms() override {
        cout<<"Modern has no Arms\n";
        return false;
    }
};

//Abstract Product-1
class Sofa {
    public:
        virtual ~Sofa() {}
        virtual bool hasLegs() = 0;
};

class ArtDecoSofa : public Sofa {
    public:
    ArtDecoSofa() {
        cout<<"Sofa of ArtDeco type created\n";
    }
    bool hasLegs() override {
        cout<<"ArtDeco Sofa has legs\n";
        return true;
    }
};

class VictorianSofa : public Sofa {
    public:
    VictorianSofa() {
        cout<<"Sofa of Victorian type created\n";
    }
    bool hasLegs() override {
        cout<<"Victorian Sofa has legs\n";
        return true;
    }
};

class ModernSofa : public Sofa {
    public:
    ModernSofa() {
        cout<<"Sofa of Modern type created\n";
    }
    bool hasLegs() override {
        cout<<"Modern Sofa has no legs\n";
        return false;
    }
};

//Fctory abstract
class FurnitureFactory {
    public:
        virtual ~FurnitureFactory() {}
        virtual Chair* createChair() = 0;
        virtual Sofa* createSofa() = 0;
    
    bool createOrder() {
        Chair* chair = this->createChair();
        Sofa* sofa = this->createSofa();
        cout<<"Printing Details:\n";
        chair->hasLegs();
        chair->hasArms();
        sofa->hasLegs();
        delete chair;
        delete sofa;
        return true;
    }
};

//concrete factory
class ArtDecoFurnitureFactory : public FurnitureFactory {
    public:
    ArtDecoFurnitureFactory() {
        cout<<"ArtDeco Factory triggered\n";
    }

    Chair* createChair() override {
        return new ArtDecoChair();
    }

    Sofa* createSofa() override {
        return new ArtDecoSofa();
    }
};

class VictorianFurnitureFactory : public FurnitureFactory {
    public:
    VictorianFurnitureFactory() {
        cout<<"Victorian Factory triggered\n";
    }

    Chair* createChair() override {
        return new VictorianChair();
    }

    Sofa* createSofa() override {
        return new VictorianSofa();
    }
};

class ModernFurnitureFactory : public FurnitureFactory {
    public:
    ModernFurnitureFactory() {
        cout<<"Modern Factory triggered\n";
    }

    Chair* createChair() override {
        return new ModernChair();
    }

    Sofa* createSofa() override {
        return new ModernSofa();
    }
};

void manageOrder(string input) {
    FurnitureFactory* fFactory;
    if(input == "ArtDeco")
        fFactory = new ArtDecoFurnitureFactory();
    else if(input=="Victorian")
        fFactory = new VictorianFurnitureFactory();
    else
        fFactory = new ModernFurnitureFactory();
    fFactory->createOrder();
}

int main() {
    string variant;
    cout<<"Enter Furniture variant (ArtDeco, Victorian, Modern): ";
    cin>>variant;
    manageOrder(variant);
    return 0;
}