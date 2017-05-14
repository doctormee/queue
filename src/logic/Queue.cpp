/*#pragma once
#include <vector>
#include <memory>
class User;
class Rule;

class Queue {
    struct Item {
        std::unique_ptr<User> user;
        int priority;
        Item(User *);
        void set_priority(int);
    };
    std::vector<std::unique_ptr<Item>> container;
    static bool queue_less(const std::unique_ptr<Item> &, const std::unique_ptr<Item> &);
public:
    Queue();
    void push(User* ); //push(new User(...));
    void remove(int); //removes a user with a specific UID from queue
    void sort();
    int size();
    std::vector<std::unique_ptr<Item>>::iterator begin();
    std::vector<std::unique_ptr<Item>>::iterator end();
    //void update(std::vector<std::unique_ptr<Rule>> &);
};
*/
#include "Queue.h"
#include "User.h"
#include <algorithm>
Queue::Queue() {}
void Queue::push(std::unique_ptr<User> &user_) {
    std::unique_ptr<Item> tmp(new Item(std::move(user_)));
    container.push_back(std::move(tmp));
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

bool Queue::queue_less(const std::unique_ptr<Item> &left, const std::unique_ptr<Item> &right) {
    return (left->priority >= right->priority);
}

void Queue::sort() {
    std::sort(container.begin(), container.end(), Queue::queue_less);
}

std::vector<std::unique_ptr<Queue::Item>>::iterator Queue::begin() {
    return container.begin();
}
std::vector<std::unique_ptr<Queue::Item>>::iterator Queue::end() {
    return container.end();
}

int Queue::size() {
    return container.size();
}

User &Queue::get_user(int uid) {
    for (auto i = container.begin(); i != container.end(); ++i) {
        if (((*i)->user->get_uid()) == uid) {
            return *((*i)->user);
        }
    }
    throw std::out_of_range("No such User!");
}
