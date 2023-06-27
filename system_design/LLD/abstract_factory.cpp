/*
Link: https://sourcemaking.com/design_patterns/abstract_factory
Link: https://www.youtube.com/watch?v=17i8a-pUtx8&list=PLliXPok7ZonlZJuAN0hvUnf5ovFepjxU0&index=7
*/


#include<bits/stdc++.h>

using namespace std;


class ITextBox {
    public:
        virtual void printText() = 0;
};

class IButton {
    public:
        virtual void press() = 0;
};

class winTextBox: public ITextBox {
    public:
        void printText() {
            cout<<"Windows.logText();\n";
        }
};

class winButton: public IButton {
    public:
        void press() {
            cout<<"Windows.click();\n";
        }
};

class linuxTextBox: public ITextBox {
    public:
        void printText() {
            cout<<"Linux.logText();\n";
        }
};

class linuxButton: public IButton {
    public:
        void press() {
            cout<<"Linux.click();\n";
        }
};

class Ifactory {
    public:
        virtual ITextBox* createTextBox() = 0;
        virtual IButton* createButton() = 0;
};
class linuxfactory: public Ifactory {
    public:
        ITextBox* createTextBox() {
            return new linuxTextBox;
        }
        IButton* createButton() {
            return new linuxButton;
        }
};

class winfactory: public Ifactory {
    public:
        ITextBox* createTextBox() {
            return new winTextBox;
        }
        IButton* createButton() {
            return new winButton;
        }
};

class GUIAbstractFactory {
    public:
        static Ifactory* createFactory(string osType) {
            if(osType == "windows") return new winfactory;
            else if (osType == "linux") return new linuxfactory;
            else return new linuxfactory;
        }
};



int main() {
    string osType;
    cout<<"Enter OS: ";
    cin>>osType;
    Ifactory* fact = GUIAbstractFactory::createFactory(osType);

    ITextBox* textBox = fact->createTextBox();
    textBox->printText();

    IButton* button = fact->createButton();
    button->press();

}