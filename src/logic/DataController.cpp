/* //#ifndef ROOMCONTROLLER_H
#define ROOMCONTROLLER_H
#include <vector>
#include <memory>
class Specialist;
class Queue;
class User;
class Rule;
class DataController {
    struct Room {
        int rid;
        std::unique_ptr<Specialist> specialist;
        std::unique_ptr<Queue> queue;
        Room(int);
        };
    std::vector<std::unique_ptr<Rule>> rules;
public:
    //DataController();
    int matching_rules(User&, User&) const;
    bool evaluate(Rule &, int, User&) const;
    bool update(Queue &); //
};
#endif*/
#include "DataController.h"
#include "Rule.h"
#include "Constants.h"
#include "User.h"
#include "Queue.h"
#include "Specialist.h"

DataController::Room::Room(int rid_, std::string spec_name, std::string spec_surname): rid(rid_), specialist(new Specialist(spec_name, spec_surname)) {} 

int DataController::matching_rules(User &user1, User &user2) const {
    /*int ret = 0;
    for (auto &i: rules) {
        ret += i->evaluate_first(user1) && i->evaluate_second(user2);
    }
    return ret; */
    return 0;
}
void DataController::update(Queue &q) {
    /*
    int priority;
    for (auto &&i = q.begin(); i != q.end(); ++i) {
        priority = 0;
        for (auto &&j = i + 1; j != q.end(); ++j) {
            priority += matching_rules(*((*i)->user), *((*j)->user));
        }
        (*i)->set_priority(priority);
    }
    q.sort();
    */
}