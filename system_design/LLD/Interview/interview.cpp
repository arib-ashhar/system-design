#include<bits/stdc++.h>

using namespace std;

class document {
    public:
        int doc_id;
        string text;
        unordered_map<string, int> hashMap;
};

Search term: Apple
Doc1: apple is a fruit
Doc2: apple come on apple
Doc3: orange are sour
Doc4: apple fruit is sweet

(1, 1)
(2, 1)
(1, 4)

// apple orange mango
class dataSet {
    public:
        unordered_map<string, unordered_map<int, pair<count, int>>> hashMap;
    vector<document*> search (string searchTerm) {
        
    }

    void addDocument(string text) {
        document* doc = new document;
        stringstream ss(text);
        string word;
        while(word >> ss) {
            doc->hashMap[word].push_back(make_pair());
        }
        //added doc_id
        doc->text = text;
        dataset.push_back(doc);
    }
    public:
    strategy* _strategy;
    setStrategy(string pStrategy) {
        if(pStrategy == "search acc to word")
            this->_strategy = new wordFreqStrategy;
    }
};

class serviceDBFactory {    
    serviceDBFactory* getDB() {
        serviceDBFactory->DBFactory
    }
}

class DBFactory: public serviceDBFactory {
    DBFactory = new dataSetFormat2
    virtual void implemetDB() = 0;
}

class dataSetFormat1: public DBFactory {
    void implemetDB(){
        
    }
}
}

class strategy {
    public:
        virtual void searchStrategy() = 0;
};

class wordFreqStrategy: public strategy {
    void search searchStrategy() {
        stringstream ss(searchTerm);
        priority_queue<pair<count, id>> maxHeap;
        vector<>
        while(word >> ss) {
            for(auto doc:dataset) {
                count, id
                pair<count, it>
                
                doc->hashMap[]
            }
        }
    }
};

class  insertionDatestrategy: public strategy {

};




int main() {
    dataSet* driver = new dataSet;
    driver.setstrategy("sort acc to word freq");
    serviceDBFactory->DBFactory->implementDB
    return 0;
}