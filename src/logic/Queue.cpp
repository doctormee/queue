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
    void remove(int);
};*/
#include "Queue.h"
#include "User.h"
#include <algorithm>
Queue::Item::Item(User *user_): user(user_), priority(0) {}
void Queue::push(User* user_) {
    std::unique_ptr<Item> tmp(new Item(user_));
    container.push_back(std::move(tmp));
}
void Queue::Item::set_priority(int priority_) {
    priority = priority_;
}
/*
void Queue::update(std::vector<std::unique_ptr<Rule>> &rules) {
    for (auto &i: container) {
        i->priority = 0;
        for (auto &j: container) {
            for (auto &k:rules) {
                i->priority += (*k)(*(i->user), *(j->user));
            }
        } 
    }
} */
void Queue::remove(int uid) {
    for (auto i = container.begin(); i != container.end(); ++i) {
        if (((*i)->user->get_uid()) == uid) {
            container.erase(i);
            break;
        }
    }
}

bool queue_less(const std::unique_ptr<Item> &left, const std::unique_ptr<Item> &right) {
    return (left->priority < right->priority);
}

void Queue::sort() {
    sort(container.begin(), container.end(), queue_less);
}