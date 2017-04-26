#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H
#include <vector>
#include <memory>
#include <map>
class Specialist;
class Queue;
class User;
class Rule;
class DataController {
    struct Room {
        int rid;
        std::unique_ptr<Specialist> specialist;
        std::unique_ptr<Queue> queue;
        Room(int, std::string, std::string);
        };
    std::map<int, std::unique_ptr<Room>> rooms;
    std::vector<std::unique_ptr<Rule>> rules;
public:
    //DataController();
    int matching_rules(User&, User&) const;
    bool evaluate(Rule &, int, User&) const;
    void update(Queue &);
};
#endif