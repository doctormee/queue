#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <memory>
#include "User.h"
#include "Rule.h"

class Queue {
    struct Item {
        std::unique_ptr<User> user;
        int priority;
        Item(User *);
    };
    std::vector<Item> queue;
    int top;
public:
    void push(User* );
    void update(std::vector<Rule>);
    void remove(int);
};
#endif