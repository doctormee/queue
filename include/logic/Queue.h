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
        void set_priority(int);
    };
    std::vector<std::unique_ptr<Item>> container;
    static bool queue_less(const std::unique_ptr<Item> &, const std::unique_ptr<Item> &) const;
public:
    Queue();
    void push(User* );
    void remove(int); //removes a user with a specific UID from queue
    void sort();
};
#endif