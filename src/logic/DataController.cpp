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
#include "Evaluator.h"
#include "Predicate.h"
#include <stdexcept>
#include <memory>

DataController::Room::Room(int rid_, std::unique_ptr<Specialist> &spec): rid(rid_), specialist(std::move(spec)), queue(new Queue()) {} 

void DataController::add_room(int rid, std::string name, std::string surname, std::vector<std::string> services) {
    std::unique_ptr<Specialist> tmp(new Specialist{name, surname});
    for (auto &i: services) {
        tmp->add_service(i);
    }
    rooms[rid] = (std::unique_ptr<Room>)(new Room(rid, tmp));
}

void DataController::delete_room(int rid) {
    decltype(rooms.begin()) it = rooms.find(rid);
    if (it == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    rooms.erase(it);
}

void DataController::update_room(int rid) {
    decltype(rooms.begin()) it = rooms.find(rid);
    if (it == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    auto &q = rooms[rid]->queue;
    int priority;
    for (auto &&i = q->begin(); i != q->end(); ++i) {
        priority = 0;
        for (auto &&j = q->begin(); j != i; ++j) {
            priority += matching_rules(*((*i)->user), *((*j)->user));
        }
        for (auto &&j = i + 1; j != q->end(); ++j) {
            priority += matching_rules(*((*i)->user), *((*j)->user));
        }
        (*i)->set_priority(priority);
    }
    q->sort();
}

void DataController::update_all() {
    for (auto &i: rooms) {
        update_room(i.first);
    }
}

void DataController::add_rule(std::unique_ptr<Rule> &rule) {
    rules.push_back(std::move(rule));
    update_all();
}

void DataController::delete_rule(int num) {
    if ((num >= rules.size()) || (num < 0)) {
        std::out_of_range ex("Нет такого правила");
        throw ex;
    }
    rules.erase(rules.begin() + num); 
    update_all();
}


int DataController::matching_rules(User &user1, User &user2) const {
    int ret = 0;
    Evaluator eval;
    for (auto &i: rules) {
        ret += (eval.set_user(&user1), i->get_first()->accept(eval), eval.get_answer()) && (eval.set_user(&user2), i->get_second()->accept(eval), eval.get_answer());
    }
    return ret;
}

Queue &DataController::get_queue(int rid) {
    decltype(rooms.begin()) it = rooms.find(rid);
    if (it == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    return *(rooms[rid]->queue);
}

Specialist &DataController::get_specialist(int rid) {
    decltype(rooms.begin()) it = rooms.find(rid);
    if (it == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    return *(rooms[rid]->specialist);
}


void DataController::add_user(int rid, int uid, std::string name, std::string surname, int age, int height, int weight, char gender)
 {
    decltype(rooms.begin()) it = rooms.find(rid);
    if (it == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    std::unique_ptr<User> tmp(new User{uid, name, surname, age, height, weight, gender});
    rooms[rid]->queue->push(tmp);
    update_room(rid);
}
void DataController::add_user(int rid, std::unique_ptr<User> &user) {
    decltype(rooms.begin()) it = rooms.find(rid);
    if (it == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    it->second->queue->push(user);
    update_room(rid);
}
void DataController::delete_user(int rid, int uid) {
    decltype(rooms.begin()) it = rooms.find(rid);
    if (it == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    it->second->queue->remove(uid);
    update_room(rid);
}

int DataController::room_size(int rid) {
    decltype(rooms.begin()) it = rooms.find(rid);
    if (it == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    return it->second->queue->size();
}
