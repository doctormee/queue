/*#ifndef ROOMCONTROLLER_H
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
#endif */
#include "Rule.h"
#include "Constants.h"

bool RoomController::evaluate(Rule &rule, int side, User& user) const{
    int u_value;
    Field field = rule.get_field(side);
    Sign sign = rule.get_sign(side);
    switch (field) {
        //ALL, AGE, HEIGHT, WEIGHT, GENDER
        case ALL: {
            return true;
        }
        case AGE: {
            u_value = user.get_age();
            break;
        }
        case HEIGHT: {
            u_value = user.get_height();
            break;
        }
        case WEIGHT: {
            u_value = user.get_weight();
            break;
        }
        case GENDER: {
            u_value = user.get_gender();
            break;
        }
        default: {
            return false;
        }
    }
    switch (sign) {
        case LESS: {
            return (u_value < value);
        }
        case LESSEQ: {
            return (u_value <= value);
        }
        case EQ: {
            return (u_value == value);
        }
        case MOREEQ: {
            return (u_value >= value);
        }
        case MORE: {
            return (u_value > value);
        }
        case NOTEQ: {
            return (u_value != value);
        }
        default: {
            return false;
        }
    }
}
int RoomController::matching_rules(User &user1, User &user2) const {
    int ret = 0;
    for (auto &i: rules) {
        ret += evaluate(i, 1, user1) && evaluate(i, 2, user2);
    }
    return ret;
}