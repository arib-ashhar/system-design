/*
Link: https://refactoring.guru/design-patterns/composite


Same Product/Box problem
We can also do folder/file problem
*/



#include<bits/stdc++.h>

using namespace std;

//Item interface
class Item {
    protected:
        Item* parent;
        string name;
    public:
        virtual ~Item() {}
        void setParent(Item* _parent) {
            this->parent = _parent;
        }
        Item* getParent() {
            return this->parent;
        }
        
        virtual void addChild(Item* item) {}
        virtual void removeChild(Item* item) {}
        virtual bool IsBox()  {
            return true;
        }
        virtual void execute()  = 0;

};

//Composite class
class Box : public Item{
    protected:
        vector<Item*> childItems;
    public:
        Box(string _name) {
            this->name = _name;
        }
        void addChild(Item* item) override {
            this->childItems.push_back(item);
            item->setParent(this);
        }
        virtual void removeChild(Item* item) override {
            //this->childItems.remove(item);
            item->setParent(nullptr);
        }
        bool IsBox()  override {
            return true;
        }
        void execute()  override {
            cout<<"this is a "<<this->name<<endl;
            for(auto item: this->childItems) {
                item->execute();
            }
        }

};

//leaf class
class Product : public Item{
    public:
        Product(string _name) {
            this->name = _name;
        }
        bool IsBox()  override {
            return false;
        }
        void execute()  override {
            cout<<"this is a "<<this->name<<endl;
        }

};

void clientCode(Item* item) {
    item->execute();
}

int main() {
    Box* box1 = new Box("box1");
    Box* box2 = new Box("Box2");
    Box* box3 = new Box("Box3");
    Box* box4 = new Box("Box4");
    Box* box5 = new Box("Box5");
    Product* hammer = new Product("hammer");
    Product* phone = new Product("Phone");
    Product* headphone = new Product("headphone");
    Product* charger = new Product("charger");
    Product* receipt = new Product("Receipt");
    box1->addChild(box2);
    box1->addChild(box3);
    box1->addChild(receipt);
    box2->addChild(hammer);
    box3->addChild(box4);
    box3->addChild(box5);
    box4->addChild(phone);
    box4->addChild(headphone);
    box5->addChild(charger);

    box1->execute();

    return 0;
}