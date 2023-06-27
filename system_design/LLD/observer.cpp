/*
Link: https://www.youtube.com/watch?v=gbTWHeGUeXs&list=PLliXPok7ZonlZJuAN0hvUnf5ovFepjxU0&index=5
Link: https://sourcemaking.com/design_patterns/observer
*/

#include<bits/stdc++.h>

using namespace std;

class User {
    private:
        int user_id;
    public:
        User(int id) {
            this->user_id = id;
        }
        void notify(string message) {
            cout<<"User ID: "<<user_id<<" recieved message: "<<message<<endl;
        }
};

class Group {
    private:
        list<User*> subscribers;
    public:
        void subscribe(User* user) {
            subscribers.push_back(user);
        }
        void unsubscribe(User* user) {
            subscribers.remove(user);
        }
        void notify(string message) {
            for(auto user:subscribers)
                user->notify(message);
        }

};

int main() {
    Group* group = new Group;
    vector<User*> users;
    for(int i=0;i<3;i++)
        users.push_back(new User(i));

    for(int i=0;i<3;i++)
        group->subscribe(users[i]);

    group->notify("First message");
    group->unsubscribe(users[2]);
    group->notify("Second message");
    return 0;
}