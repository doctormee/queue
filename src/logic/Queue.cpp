/*class Queue {
    struct Item {
        std::unique_ptr<User> user;
        int priority;
        Item(User *);
    };
    std::vector<std::unique_ptr<Item>> container;
    int top;
public:
    void push(User* );
    void update(std::vector<std::unique_ptr<Rule>> &);
    void remove(int);
};*/
#include "Queue.h"
#include "User.h"
Queue::Item::Item(User *user_): user(user_), priority(0) {}
void Queue::push(User* user_) {
    std::unique_ptr<Item> tmp(new Item(user_));
    container.push_back(std::move(tmp));
}
void Queue::update(std::vector<std::unique_ptr<Rule>> &rules) {
    for (auto &i: container) {
        i->priority = 0;
        /*for (auto &j: container) {
            for (auto &k:rules) {
                //i->priority += (*k)(*(i->user), *(j->user));
            }
        } */
    }
}