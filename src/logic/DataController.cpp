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

void DataController::add_room(
    int rid, 
    std::string name, 
    std::string surname, 
    std::vector<std::string> services) 
{
    std::unique_ptr<Specialist> tmp{new Specialist{name, surname}};
    for (auto const &service: services) {
        tmp->add_service(service);
    }
    rooms[rid] = (std::unique_ptr<Room>){new Room{rid, tmp}};
}

void DataController::delete_room(int rid) {
    auto room = rooms.find(rid);
    if (room == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    rooms.erase(room);
}

void DataController::update_room(int rid) {
    auto room = rooms.find(rid);
    if (room == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    auto &queue = rooms[rid]->queue;
    int priority;
    for (auto &item: *queue) {
        priority = 0;
        for (auto &other_item: *queue) {
            if (item != other_item) {
                priority += matching_rules(*(item->user), *(other_item->user));
            }
        }
        item->set_priority(priority);
    }
    queue->sort();
}

void DataController::update_all() {
    for (auto &room: rooms) {
        update_room(room.first);
    }
}

void DataController::add_rule(std::unique_ptr<Rule> &rule) {
    rules.push_back(std::move(rule));
    update_all();
}

std::vector<Rule *> DataController::get_rules() {
    std::vector<Rule *> tmp;
    for (auto const &rule: rules) {
        tmp.push_back(rule.get());
    }
    return tmp;
}

void DataController::delete_rule(int num) {
    if ((num >= rules.size()) || (num < 0)) {
        std::out_of_range ex("Нет такого правила!");
        throw ex;
    }
    rules.erase(rules.begin() + num); 
    update_all();
}


int DataController::matching_rules(User &user1, User &user2) const {
    int ret = 0;
    Evaluator eval;
    for (auto const &rule: rules) {
        eval.set_user(&user1);
        rule->get_first()->accept(eval);
        eval.set_user(&user2);
        ret += eval.get_answer() && (rule->get_second()->accept(eval), eval.get_answer());
    }
    return ret;
}

Queue &DataController::get_queue(int rid) {
    decltype(rooms.begin()) room = rooms.find(rid);
    if (room == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    return *(rooms[rid]->queue);
}

Specialist &DataController::get_specialist(int rid) {
    decltype(rooms.begin()) room = rooms.find(rid);
    if (room == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    return *(rooms[rid]->specialist);
}

void DataController::add_user(
    int rid, 
    int uid, 
    std::string name, 
    std::string surname, 
    int age, 
    int height, 
    int weight, 
    char gender)
 {
    decltype(rooms.begin()) room = rooms.find(rid);
    if (room == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    std::unique_ptr<User> tmp{new User{uid, name, surname, age, height, weight, gender}};
    rooms[rid]->queue->push(tmp);
    update_room(rid);
}

void DataController::add_user(
    int rid, 
    std::unique_ptr<User> &user) 
{
    decltype(rooms.begin()) room = rooms.find(rid);
    if (room == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    room->second->queue->push(user);
    update_room(rid);
}

void DataController::delete_user(int rid, int uid) {
    decltype(rooms.begin()) room = rooms.find(rid);
    if (room == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    room->second->queue->remove(uid);
    update_room(rid);
}

int DataController::room_size(int rid) {
    decltype(rooms.begin()) room = rooms.find(rid);
    if (room == rooms.end()) {
        std::out_of_range ex("Нет комнаты с таким номером!");
        throw ex;
    }
    return room->second->queue->size();
}
