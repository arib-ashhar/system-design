/*
Link: https://refactoring.guru/design-patterns/state


Same Document problem
*/


#include<bits/stdc++.h>

using namespace std;

class Document;

// State interface
class IDocumentState {
    protected:
        Document* document;
    public:
        string name;
        IDocumentState(string _name, Document* doc) {
            this->name = _name;
            this->document = doc;
        }
        virtual ~IDocumentState() {}
        IDocumentState(Document* _document) {
            this->document = _document;
        }
        virtual void render() = 0;
        virtual void publish() = 0;
};

//context class
class Document {
    protected:
        IDocumentState* docState;
    public:
        void changeState(IDocumentState* newState) {
            this->docState = newState;
            cout<<"Document state changed to "<<newState->name<<endl;
        }

        void render() {
            this->docState->render();
        }
        void publish() {
            this->docState->publish();
        }
};

//concrete states
class PublishState : public IDocumentState {
    public:
        PublishState(string name, Document* doc) : IDocumentState(name, doc) {}
        void render() override {
            cout<<"Rendering Publish"<<endl;
        }
        void publish() override {
            cout<<"Publish PublishVersion by User"<<endl;
        }
};

class ModerationState : public IDocumentState {
    public:
        ModerationState(string name, Document* doc) : IDocumentState(name, doc) {}
        void render() override {
            cout<<"Rendering Moderation"<<endl;
        }
        void publish() override {
            cout<<"Publish Moderation by User"<<endl;
            this->document->changeState(new PublishState("Publish State", this->document));
        }
};

class DraftState : public IDocumentState {
    public:
        DraftState(string name, Document* doc) : IDocumentState(name, doc) {}
        void render() override {
            cout<<"Rendering Draft"<<endl;
        }
        void publish() override {
            cout<<"Publish Draft by User"<<endl;
            this->document->changeState(new ModerationState("Moderation State", this->document));
        }
};

int main() {
    Document* doc = new Document();
    doc->changeState(new DraftState("draft", doc));
    doc->render();
    doc->publish();

    doc->render();
    doc->publish();

    doc->render();
    doc->publish();
    return 0;
}