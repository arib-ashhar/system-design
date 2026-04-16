/*
Link: https://refactoring.guru/design-patterns/observer


Same Pub-Sub example
*/



#include<bits/stdc++.h>

using namespace std;

//sub interface
class ISubscriber {
    public:
        string name;
        virtual void sendNotification() = 0;
};

//interface for Pub
class IPublisher {
    public:
        virtual void subscribe(ISubscriber* sub) = 0;
        virtual void unsubscribe(string subName) = 0;
        virtual void Notify() = 0;
};

// publisher
class Publisher : public IPublisher {
    public:
        unordered_map<string, ISubscriber*> subcribers;
        void subscribe(ISubscriber* sub) override {
            subcribers[sub->name] = sub;
            cout<<"subscriber "<<sub->name<<" added"<<endl;
        }

        void unsubscribe(string subName) override {
            if(subcribers.find(subName) != subcribers.end()) {
                subcribers.erase(subName);
            }
            cout<<"subscriber "<<subName<<" removed"<<endl;
        }

        void Notify() override {
            for(auto [subName, sub]:subcribers) {
                sub->sendNotification();
            }
        }
};



// concrete sub class
// NOTE their can be multiple subscripber class
class Subscriber : public ISubscriber {
    public:
        Subscriber(string _name) {
            this->name = _name;
        }

        void sendNotification() override {
            cout<<"Sending notification to "<<this->name<<endl;
        }
};


int main() {
    Publisher* pub = new Publisher();
    for(int i=1;i<=3;i++) {
        Subscriber* sub = new Subscriber("Sub" + to_string(i));
        pub->subscribe(sub);
    }
    pub->Notify();

    pub->unsubscribe("Sub2");
    pub->Notify();
    return 0;
}

