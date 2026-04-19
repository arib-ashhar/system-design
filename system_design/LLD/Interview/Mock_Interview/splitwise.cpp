#include<bits/stdc++.h>

using namespace std;

/*

- user create a group, multiple members
- all members can add transaction, select all the participants
- participants can clear debt
- no concurrency
- users should be able to see their balance (whether they owe or they lend)
- Notification


Entitites
- Group
- members
- User
- transaction
- transaction type (created, cleared)
- split type (equal, percentage..)





*/

enum TransactionStatus {
    CREATED,
    CLEARED
};


class Group {
    private:
        string name;
        int id;
        vector<User*> members;
    public:

};

class User {
    private:
        int id;
        int emailAddress;
    public:

};

class Balance {
    private:
        double amountOwed;
        double amountLend;
        Group* group;
        User* user;
};


class Transaction {
    private:
        int id;
        Group* group;
        vector<User*> participants;
        TransactionStatus status;
        double amount;
        User* owner;
    public:

};




class SplitStrategy {
    public:
        virtual vector<pair<User*, double>> processSplit(vector<pair<User*, double>> participants, double amount) = 0;
};

class EqualSplit : public SplitStrategy {
    public:
        vector<pair<User*, double>> processSplit(vector<pair<User*, double>> participants, double amount) override {
            // Loop all the participant
            // equally distribute the amount
        }
};

class PercentageSplit : public SplitStrategy {
    public:
        vector<pair<User*, double>> processSplit(vector<pair<User*, double>> participants, double amount) override {
            // Loop all the participant
            // distribute the percentage for each participant
        }
};

class TransactionService {
    public:
        Transaction* createTrasaction(Group* group, vector<User*> participants, double amount, SplitStrategy* SplitStrategy, User* owner) {
            // 
        }

        bool cancelTransaction() {
            // delete it
        }
};

class GroupService {
    private:
        unordered_map<int, Group*> groups;
        atomic<int> groupCount{0};
    public:
        Group* createGroup(string name) {
            
        }

        bool join(Group* group, User* user) {

        }

        bool leave(Group* group, User* user) {

        }
};

class BalanceService {
    private:

    public:
        double getTotalBalance(User* user) {
            // For all the groups for user
            // add all the lent amount
            // minus all the owed amount
            // return the totalAmount;
        }

        map<User*, double> amountOwed(Group* group, User* user) {
            // in this group
            // return all the user, amount who owes me
        }

        map<User*, double> amountLend(Group* group, User* user) {
            // in this group
            // return all the user, amount who I have lent
        }

        double totalAmoutOwed(User* user) {

        }

        double totalAmountLend(User* user) {

        }

        bool settleBalance(Group* group, User* user) {
            // for this user in group
            // settle all the pending debts
        }
};