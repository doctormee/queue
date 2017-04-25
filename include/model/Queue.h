#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <memory>
#include "User.h"

class Queue {
    struct Item {
        std::shared_ptr<User> user;
        int priority;
        Item(std::shared_ptr<User>);
    };
    std::vector<Item> queue;
    int top;
public:
    void push(std::shared_ptr<User>);
    void update();
    void remove(int);
};
#endif