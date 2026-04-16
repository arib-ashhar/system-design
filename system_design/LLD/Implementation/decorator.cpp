/*
Link: https://refactoring.guru/design-patterns/decorator


Same Notifier example
*/



#include<bits/stdc++.h>

using namespace std;

//component interface
class Notifier {
    public:
        Notifier() {}
        virtual void sendNotification() = 0;
};

//concrete component
class EmailNotifier : public Notifier {
    public:
        void sendNotification() override {
            cout<<"Sending email notification"<<endl;
        }
};


//Base Decorator Interface
class BaseNotifierDecorator : public Notifier {
    public:
        Notifier* wrappee;
        BaseNotifierDecorator(Notifier* notifier) : wrappee(notifier) {}
        void sendNotification() override {
            wrappee->sendNotification();
        }
};

//concrete Decorator
class FacebookNotifier : public BaseNotifierDecorator {
    public:
        FacebookNotifier(Notifier* notifier) : BaseNotifierDecorator(notifier) {}
        void sendNotification() override {
            cout<<"Sending facebook notification"<<endl;
            this->wrappee->sendNotification();
        }
};

//concrete Decorator 2
class SMSNotifier : public BaseNotifierDecorator {
    public:
        SMSNotifier(Notifier* notifier) : BaseNotifierDecorator(notifier) {}
        void sendNotification() override {
            cout<<"Sending SMS notification"<<endl;
            this->wrappee->sendNotification();
        }
};

//concrete Decorator 3
class SlackNotifier : public BaseNotifierDecorator {
    public:
        SlackNotifier(Notifier* notifier) : BaseNotifierDecorator(notifier) {}
        void sendNotification() override {
            cout<<"Sending Slack notification"<<endl;
            this->wrappee->sendNotification();
        }
};

int main() {
    Notifier* notifier = new EmailNotifier();
    Notifier* smsNotifer = new SMSNotifier(notifier);
    Notifier* facebookNotifier = new FacebookNotifier(smsNotifer);
    Notifier* slackNotifier = new SlackNotifier(facebookNotifier);
    slackNotifier->sendNotification();
    return 0; 
}
