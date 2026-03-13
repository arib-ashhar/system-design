/*
Link: https://refactoring.guru/design-patterns/singleton

Same DB instance problem

*/


#include<bits/stdc++.h>

using namespace std;

// This is the Singleton class
class DB {
    private:
        static DB* instance;
        static mutex mutex_;
    
    protected:
        string connectionString;
        DB(const string _connectionString): connectionString(_connectionString) {}
        ~DB() {}
    
    public:
        DB(DB& dbConnection) = delete;
        void operator=(const DB& dbConnection) = delete;

        static DB* getInstance(const string connectionString);
        bool save() {
            cout<<"save data in "<<connectionString<<endl;
            return true;
        }
};

DB* DB::instance{nullptr};
mutex DB::mutex_;

// static method definition for getInstance (with thread safety)
DB* DB::getInstance(const string connectionString) {
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance == nullptr) {
        instance = new DB(connectionString);
    }
    return instance;
}

void ThreadExecute(const string& connectionString) {
    DB* dbInstance = DB::getInstance(connectionString);
    dbInstance->save();
}

int main() {
    cout<<"Testing Singleton class with two threads: \n";
    std::thread t1(ThreadExecute, "connection1");
    std::thread t2(ThreadExecute, "connection2");
    t1.join();
    t2.join();
    return 0;
}

/*
OUTPUT:
Testing Singleton class with two threads: 
save data in save data in connection1
connection1

// The cout min alignment is because which ever thread takes hold out cout first and the order of execution is decided on that.
// If we want we can add mutex for cout and fix that as well.
*/