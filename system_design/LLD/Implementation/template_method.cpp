/*
Link: https://refactoring.guru/design-patterns/template-method


Same Date Mining Application
*/

#include<bits/stdc++.h>

using namespace std;

// base template method with some default implementation and some interface for concrete class to inherit
class DataMiner {
    public:
        void mine(string path, string fileName) {
            cout<<"Mining: "<<path<<endl;
            string data = openFile(fileName);
            string extractedData  = extractData(data);
            string parsedData = parseData(extractedData);
            string analysis = analyzeData(parsedData);
            string result = sendReport(analysis);
            closeFile(fileName);
        }

        virtual string openFile(string fileName) = 0;
        virtual string extractData(string data) = 0;
        virtual string parseData(string data) = 0;
        string analyzeData(string input) {
            cout<<"Analyzing Data (Default Implementation)"<<endl;
            return "Anlyzed Data: " + input;
        }

        string sendReport(string input) {
            cout<<"Sending Report (Default Implementation)"<<endl;
            return "Report: " + input;
        }

        virtual void closeFile(string fileName) = 0;
};


//Concrete SubClass
class PDFDataMiner : public DataMiner {
    public:

        string openFile(string fileName) override {
            cout<<"Opening PDF File: "<<fileName<<endl;
            return "PDF Data from " + fileName;
        }
        string extractData(string data) override {
            cout<<"Extracting: "<<data<<endl;
            return "Extracted Data from: " + data;
        }
        string parseData(string data) override {
            cout<<"Parsing: "<<data<<endl;
            return "Parsed Data from: " + data;
        }

        void closeFile(string fileName) override {
            cout<<"Closing PDF File: "<<fileName<<endl;
        }
};

class CSVDataMiner : public DataMiner {
    public:

        string openFile(string fileName) override {
            cout<<"Opening CSV File: "<<fileName<<endl;
            return "CSV Data from " + fileName;
        }
        string extractData(string data) override {
            cout<<"Extracting: "<<data<<endl;
            return "Extracted Data from: " + data;
        }
        string parseData(string data) override {
            cout<<"Parsing: "<<data<<endl;
            return "Parsed Data from: " + data;
        }

        void closeFile(string fileName) override {
            cout<<"Closing CSV File: "<<fileName<<endl;
        }
};

class DOCDataMiner : public DataMiner {
    public:

        string openFile(string fileName) override {
            cout<<"Opening DOC File: "<<fileName<<endl;
            return "DOC Data from " + fileName;
        }
        string extractData(string data) override {
            cout<<"Extracting: "<<data<<endl;
            return "Extracted Data from: " + data;
        }
        string parseData(string data) override {
            cout<<"Parsing: "<<data<<endl;
            return "Parsed Data from: " + data;
        }

        void closeFile(string fileName) override {
            cout<<"Closing DOC File: "<<fileName<<endl;
        }
};

void clientCode(DataMiner* dataMiner, string fileName, string path) {
    dataMiner->mine(path, fileName);
}

int main() {
    clientCode(new PDFDataMiner(), "trst.pdf", "C:/Files/");
    clientCode(new CSVDataMiner(), "salary.csv", "C:/Files/");
    clientCode(new DOCDataMiner(), "presentation.doc", "C:/Files/");
    return 0;
}