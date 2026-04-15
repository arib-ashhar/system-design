/*
Link: https://refactoring.guru/design-patterns/adapter


Same XML example
*/



#include<bits/stdc++.h>

using namespace std;

//Target class
class XML {
    public:
        virtual ~XML() = default;
        virtual void processRequest() const {
            cout<<"XML class has data in xml format"<<endl;
        }
};

class JSON {
    public:
        void useData() const {
            cout<<"JSON class has data in json format"<<endl;
        }
};

class Adapter: public JSON, public XML {
    public:
        Adapter() {}
        void processRequest() const override {
            useData();
            // do somethign with the data;
            cout<<"JSON Data is converted to XML inadapter"<<endl;
        }
};

void clientCode(XML* xml) {
    xml->processRequest();
}

int main() {
    clientCode(new XML());
    JSON* json = new JSON;
    clientCode(new Adapter());
    return 0;
}