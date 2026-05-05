/*

Technical Assessment: Build a High-Performance In-Memory Key-Value Store (Mini-Redis)
1. Overview
The goal of this challenge is to build a simplified version of Redis—a high-performance, in-memory data store.
2. The Problem Statement
You need to develop a cli (or a library) that provides a programmatic interface for storing and retrieving data. The system must be optimized for speed and memory efficiency, simulating how a real-world cache manages high volumes of transient data.Automatically clean expired keys without affecting the performance of main application.
Core Commands to Support
Command
Description
SET key value
Stores the value.
GET key
Retrieves the value. Returns null/nil if not found or expired.
DEL key
Removes the key from the store.
EXPIRE key seconds
Sets a timeout on a key. After the timeout, the key is deleted from memory.
TTL key
Returns the remaining Time To Live of a key in seconds.
INCR key
Increments the number stored at key by one. If key doesn't exist, set it to 0 then increment it.
DECR key
decrements the number stored at key by one. If key doesn't exist, it throws error
ALLKEYS
Shows all keys
FLUSHALL
Delete all keys

4. Deliverables
The Code: A clean, well-commented implementation. Expiry and Concurrency is properly handled with performance. 
ReadMe: Brief explanation of your chosen Expiry Cleanup Strategy and how you handled Concurrency.
All the commands should work as per expectations





*/    
    
    
    
    /*
    - clean strategy: strategy design pattern
    - IF Least Rescenty Used: Hash Map + LL
    - FCFS: queue
    
    Cache Manager: singletone


    */

    # include<bits/stdc++.h>
    using namespace std;

    class Entry {
        public:
            string key;
            int value;
            long long timeStamp;
            int expiry = -1;
    };

    // for doublly linked list
    class Node {
        public:
            Entry* entry;
            Node* prev = nullptr;
            Node* next = nullptr;
            Node(Entry* _entry) {
                this->entry = _entry;
            }

            Node() {
                this->entry = new Entry();
            }
    };

    class cacheManager {
        private:
        const int MAX_CAPACITY = 100;

            void updateLLHead(Node* node) {
                if (head->next == node) return;
                node->prev->next = node->next;
                node->next->prev = node->prev;
                node->next = head->next;
                node->prev = head;
                head->next->prev = node;
                head->next = node;
            }

            long long currentTimeStamp() {
                return chrono::duration_cast<chrono::seconds>(
                    chrono::system_clock::now().time_since_epoch()
                ).count();
            }

            void removeLRU() {
                if (keyMap.empty()) return;
                Node* lruNode = tail->prev;
                string keyToDelete = lruNode->entry->key;
                
                lruNode->prev->next = tail;
                tail->prev = lruNode->prev;

                keyMap.erase(keyToDelete);
                delete lruNode->entry;
                delete lruNode;
            }

            cacheManager() {
                head = new Node();
                tail = new Node();
                head->next = tail;
                tail->prev = head;
            }
        public:
            static cacheManager* cacheManagerInst;
            static mutex mtx;
            unordered_map<string, Node*> keyMap;
            Node* head;
            Node* tail;

            static cacheManager* getCacheManager() {
                if(cacheManagerInst == nullptr) {
                    mtx.lock();
                    if(cacheManagerInst == nullptr) {
                        cacheManagerInst = new cacheManager();
                    }
                    mtx.unlock();
                }
                return cacheManagerInst;
            }

            int setKey(string key, int value) {
                Node* node;
                if(keyMap.find(key) != keyMap.end()) {
                    Node* node = keyMap[key];
                    node->entry->value = value;
                    node->entry->timeStamp = currentTimeStamp();
                    updateLLHead(node);
                }
                else {
                    if (keyMap.size() >= MAX_CAPACITY) {
                        removeLRU();
                    }

                    Entry* entry = new Entry();
                    entry->key = key;
                    entry->value = value;
                    entry->timeStamp = currentTimeStamp();
                    node = new Node(entry);
                    keyMap[key] = node;
                    
                    // put at the start of LL
                    node->next = head->next;
                    node->prev = head;
                    head->next->prev = node;
                    head->next = node;
                }

                return 1;
            }

            int setExpiry(string key, int expiry) {
                if(keyMap.find(key) != keyMap.end()) {
                    auto& node = keyMap[key];
                    node->entry->expiry = expiry;
                }
                return 1;
            }

            string getKey(string key) {
                if(keyMap.find(key) != keyMap.end()) {
                    auto& node = keyMap[key];
                    int expiryTime = node->entry->timeStamp + node->entry->expiry;
                    int timeNow = currentTimeStamp();
                    if(node->entry->expiry > 0 && expiryTime < timeNow)
                        return "null";

                    // update the LL
                    updateLLHead(node);
                    
                    return to_string(node->entry->value);
                }
                else {
                    return "null";
                }
            }

            int delKey(string key) {
                if(keyMap.find(key) != keyMap.end()) {
                    auto& node = keyMap[key];
                    // update the LL
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                    
                    keyMap.erase(key);
                    delete node->entry;
                    delete node;
                }
                return 1;
            }

            int getTTL(string key) {
                if(keyMap.find(key) != keyMap.end()) {
                    auto& node = keyMap[key];
                    int expiryTime = node->entry->timeStamp + node->entry->expiry;
                    int timeNow = currentTimeStamp();
                    if(expiryTime > timeNow) return expiryTime - timeNow;
                    else 
                        return -1;
                }
                return -2;
            }

            int incrKey(string key) {
                if(keyMap.find(key) != keyMap.end()) {
                    auto& node = keyMap[key];
                    node->entry->value++;
                    updateLLHead(node);
                }
                else {
                    setKey(key, 0);
                }
                return 1;
            }

            int dcrKey(string key) {
                if(keyMap.find(key) != keyMap.end()) {
                    auto& node = keyMap[key];
                    node->entry->value--;
                    updateLLHead(node);
                    return 1;
                }
                else {
                    return -1;
                }
            }

            void allKeys() {
                for(auto& [key, node]: keyMap) {
                    cout<<key<<endl;
                }
            }

            void delAllKey() {
                for(auto& [key, node]: keyMap) {
                    delKey(key);
                }
            }
    };

    cacheManager* cacheManager::cacheManagerInst = nullptr;
    mutex cacheManager::mtx;

    int main(int argc, char* argv[]) {
        if (argc < 2) {
            cout << "Usage: ./redis COMMAND [ARGS]" << endl;
            return 1;
        }

        cacheManager* cache = cacheManager::getCacheManager();
        string line;
        while (true) {
            cout << "> ";
            getline(cin, line);
            if (line == "EXIT" || line == "exit") break;

            stringstream ss(line);
            string cmd, arg1, arg2;
            ss >> cmd >> arg1 >> arg2;

            if (cmd == "SET") {
                cache->setKey(arg1, stoi(arg2));
                cout << "OK" << endl;
            } 
            else if (cmd == "GET") {
                cout << cache->getKey(arg1) << endl;
            } 
            else if (cmd == "EXPIRE") {
                cache->setExpiry(arg1, stoi(arg2));
                cout << "OK" << endl;
            }
            else if (cmd == "ALLKEYS") {
                cache->allKeys();
            }
            else if(cmd == "DEL") {
                cache->delKey(arg1);
            }
            else if(cmd == "TTL") {
                cache->getTTL(arg1);
            }
            else if(cmd == "INCR") {
                cache->incrKey(arg1);
            }
            else if(cmd == "DECR") {
                cache->dcrKey(arg1);
            }
            else if(cmd == "FLUSHALL") {
                cache->delAllKey();
            }
            else
                cout<<"wrong usage"<<endl;

        }
        return 0;
    }