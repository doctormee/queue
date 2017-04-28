/*#ifndef ROOMCONTROLLER_H
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
    bool update(Queue &);
};
#endif*/
#include "DataController.h"
#include "Rule.h"
#include "Constants.h"
#include "User.h"
#include "Queue.h"
#include "Specialist.h"

DataController::Room::Room(int rid_, std::string spec_name, std::string spec_surname): rid(rid_), specialist(new Specialist(spec_name, spec_surname)) {} 

bool DataController::evaluate(Rule &rule, int side, User& user) const{
    int u_value;
    Field field = rule.get_field(side);
    Sign sign = rule.get_sign(side);
    int value = rule.get_value(side);
    switch (field) {
        //ALL, AGE, HEIGHT, WEIGHT, GENDER
        case Field::ALL: {
            return true;
        }
        case Field::AGE: {
            u_value = user.get_age();
            break;
        }
        case Field::HEIGHT: {
            u_value = user.get_height();
            break;
        }
        case Field::WEIGHT: {
            u_value = user.get_weight();
            break;
        }
        case Field::GENDER: {
            u_value = user.get_gender();
            break;
        }
        default: {
            return false;
        }
    }
    switch (sign) {
        case Sign::LESS: {
            return (u_value < value);
        }
        case Sign::LESSEQ: {
            return (u_value <= value);
        }
        case Sign::EQ: {
            return (u_value == value);
        }
        case Sign::MOREEQ: {
            return (u_value >= value);
        }
        case Sign::MORE: {
            return (u_value > value);
        }
        case Sign::NOTEQ: {
            return (u_value != value);
        }
        default: {
            return false;
        }
    }
}
int DataController::matching_rules(User &user1, User &user2) const {
    int ret = 0;
    for (auto &i: rules) {
        ret += evaluate(*i, 1, user1) && evaluate(*i, 2, user2);
    }
    return ret;
}
void DataController::update(Queue &q) {
    int priority;
    for (auto &&i = q.begin(); i != q.end(); ++i) {
        priority = 0;
        for (auto &&j = i + 1; j != q.end(); ++j) {
            priority += matching_rules(*((*i)->user), *((*j)->user));
        }
        (*i)->set_priority(priority);
    }
    q.sort();
}