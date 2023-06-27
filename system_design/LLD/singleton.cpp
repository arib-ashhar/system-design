/*
Link: https://www.youtube.com/watch?v=oeQWxhlnCHM&list=PLliXPok7ZonlZJuAN0hvUnf5ovFepjxU0&index=4
Link: https://sourcemaking.com/design_patterns/singleton/cpp/1
*/

#include<bits/stdc++.h>
#include <thread>
#include <mutex>

using namespace std;

class Logger {
    static int instanceCount;
    static Logger* loggerInstance;
    static mutex loggerInstanceMtx;
    Logger() {
        instanceCount++;
        cout<<"New Instance is created, Count="<<instanceCount<<endl;
    }
    Logger(const Logger&);
    Logger operator=(const Logger&);

    public:
        static Logger* getLogger() {
            //Double checked Locking
            if(!loggerInstance) {
                //thread safety
                loggerInstanceMtx.lock();
                if(!loggerInstance) {
                        loggerInstance = new Logger();
                }
                loggerInstanceMtx.unlock();
            }
            return loggerInstance;
        }
        void logMessage(string message) {
            cout<<"Logged Message: "<<message<<endl;
        } 
};

int Logger::instanceCount=0;
Logger* Logger::loggerInstance=nullptr;
mutex Logger::loggerInstanceMtx;

void user1logs() {
    Logger* logger1 = Logger::getLogger();
    logger1->logMessage("Message from Logger 1");
}

void user2logs() {
    Logger* logger2 = Logger::getLogger();
    logger2->logMessage("Message from Logger 2");
}  
int main() {
    thread t1(user1logs);
    thread t2(user2logs);
    t1.join();
    t2.join();
    return 0;
}