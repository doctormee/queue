#ifndef ROOMCONTROLLER_H
#define ROOMCONTROLLER_H
#include <vector>
#include <memory>
class User;
class Rule;
class RoomController {
    std::vector<std::unique_ptr<Rule>> rules;
public:
    //RoomController();
    int matching_rules(User&, User&) const;
    bool evaluate(Rule &, int, User&) const;
};
#endif