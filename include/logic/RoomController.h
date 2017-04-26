#ifndef ROOMCONTROLLER_H
#define ROOMCONTROLLER_H
#include <vector>
#include <memory>
#include <map>
class Specialist;
class Queue;
class User;
class Rule;
class RoomController {
    struct Room {
        int rid;
        std::unique_ptr<Specialist> specialist;
        std::unique_ptr<Queue> queue;
        Room(int, std::string, std::string);
        };
    std::map<int, std::unique_ptr<Room>>;
    std::vector<std::unique_ptr<Rule>> rules;
public:
    //RoomController();
    int matching_rules(User&, User&) const;
    bool evaluate(Rule &, int, User&) const;
    bool update(Queue &);
};
#endif