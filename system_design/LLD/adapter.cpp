/*
Link: https://www.youtube.com/watch?v=JxveJ1pI5fc&list=PLliXPok7ZonlZJuAN0hvUnf5ovFepjxU0&index=8
Link: https://sourcemaking.com/design_patterns/adapter
*/

#include<bits/stdc++.h>

using namespace std;

class xmlData {
    string xmldata;
    public:
        xmlData() {}
        xmlData(string data) {
            xmldata = data;
        }
        string getxmlData() {
            return xmldata;
        }
};

class dataAnalyticsTool {
    string JSONdata;
    public:
        dataAnalyticsTool() {}
        dataAnalyticsTool(string pJSONdata) {
            JSONdata = pJSONdata;
        }
        virtual void analyze() {
            cout<<"Analyzing Data: "<<JSONdata<<endl;
        }
};

class Adapter: public dataAnalyticsTool {
    xmlData* xml;
    public:
        Adapter(xmlData* data) {
            xml = data;
        }
        void analyze() override {
            cout<<"Converting XML Data: "<<xml->getxmlData()<<" to JSON"<<endl;
            cout<<"Analyzing converted Data: "<<endl;
        }
};

class Client {
    public:
        void processData(dataAnalyticsTool* tool) {
            tool->analyze();
        }
};

int main() {
    xmlData* XMLdata = new xmlData("<note><body>Hello World!</body></note>");
    dataAnalyticsTool* tool = new Adapter(XMLdata);
    Client* client = new Client;
    client->processData(tool);
    return 0;
}