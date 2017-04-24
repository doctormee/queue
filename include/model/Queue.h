#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <User.h>
#include <memory>

class Queue {
    struct Item {
        std::shared_ptr<User> user;
        int priority;
        Item(std::shared_ptr<User>);
    };
    std::vector<Item> queue;
public:
    

};
#endif