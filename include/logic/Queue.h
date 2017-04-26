#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <memory>
class User;
class Rule;

class Queue {
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
};
#endif