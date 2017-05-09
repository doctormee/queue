#pragma once
#include <vector>
#include <memory>
class User;

class Queue {
    struct Item {
        std::unique_ptr<User> user;
        int priority;
        Item(std::unique_ptr<User>);
        void set_priority(int);
    };
    std::vector<std::unique_ptr<Item>> container;
    static bool queue_less(const std::unique_ptr<Item> &, const std::unique_ptr<Item> &);
public:
    Queue();
    void push(std::unique_ptr<User> &); //push;
    void remove(int); //removes a user with a specific UID from queue
    void sort();
    int size();
    std::vector<std::unique_ptr<Item>>::iterator begin();
    std::vector<std::unique_ptr<Item>>::iterator end();
    //void update(std::vector<std::unique_ptr<Rule>> &);
};
