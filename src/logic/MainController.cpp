#include "MainController.h"
#include "UI.h"
#include "Parser.h"
#include "Rule.h"
#include "Printer.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <memory>
#include <set>

Parser MainController::parser = Parser{};
const int MainController::MAX_USERS = 100;
const int MainController::MAX_ROOMS = 10;
int MainController::get_rid() {
    if (free_rids.size() == 0) {
        throw std::out_of_range("Нельзя добавить больше специалистов!");
    }
    else {
        int tmp = free_rids.top();
        free_rids.pop();
        return tmp;
    }
}

int MainController::get_uid() {
    if (free_uids.size() == 0) {
        throw std::out_of_range("Нельзя добавить больше пользователей!");
    }
    else {
        int tmp = free_uids.top();
        free_uids.pop();
        return tmp;
    }
}

void MainController::init() {
    int i;
    for (i = (MAX_USERS - 1); i >= 0; --i) {
        free_uids.push(i);
    }
    for (i = (MAX_ROOMS - 1); i >= 0; --i) {
        free_rids.push(i);
        
    }
}

MainController::MainController() {
    init();
}

std::vector<std::string> MainController::get_services() {
    if (services_map.size() == 0) {
        throw std::logic_error("Нет доступных услуг!");
    }
    else {
        std::vector<std::string> ret;
        for (auto &i: services_map) {
            ret.push_back(i.first);
        }
        return ret;
    }
}

int MainController::add_user(std::string service, std::string name, std::string surname, int age, int height, int weight, char gender) {
    int rid, uid;
    uid = get_uid();
    auto it = services_map.find(service);
    //поиск комнаты с наименьшей очередью
    rid = it->second[0];
    for (auto &j: it->second) {
        if (database.room_size(j) < database.room_size(rid)) {
            rid = j;
        }
    }
    database.add_user(rid, uid, name, surname, age, height, weight, gender);
    users_map[uid] = rid;
    return uid;
}

void MainController::add_room(std::string name, std::string surname, std::vector<std::string> services) {
    int rid;
    rid = get_rid();
    database.add_room(rid, name, surname, services);
    for (auto &i: services) {
        services_map[i].push_back(rid);
    }
}

Queue &MainController::get_queue(int uid) {
    auto it = users_map.find(uid);
    if (it == users_map.end()) {
        throw std::logic_error("Пользователь не существует!");
    }
    auto rid = it->second;
    return database.get_queue(rid);
}

void MainController::remove_user(int uid) {
    auto it = users_map.find(uid);
    if (it == users_map.end()) {
        throw std::logic_error("Пользователь не существует!");
    }
    auto rid = it->second;
    database.delete_user(rid, uid);
    free_uids.push(uid);
    users_map.erase(uid);
}
void MainController::remove_room(int rid) {
    for (auto &i: users_map) {
        if (i.second == rid) {
            remove_user(i.first);
        }
    }
    auto &spec = database.get_specialist(rid);
    for (int i = 0; i < spec.size(); ++i) {
        std::string cur = spec.get_service(i);
        services_map[cur].erase(std::find(services_map[cur].begin(), services_map[cur].end(), rid));
    }
    database.delete_room(rid);
    free_rids.push(rid);
}
std::vector<std::string> MainController::get_rooms() {
    std::vector<std::string> ret;
    std::string msg;
    std::set<int> rids;
    for (auto &i: services_map) {
        for (auto j: i.second) {
            if (rids.find(j) == rids.end()) {
                rids.insert(j);
            }
        }
    }
    Printer print{};
    for (auto i: rids) {
        print.flush();
        Specialist &spec = database.get_specialist(i);
        msg = std::to_string(i) + ". " + (spec.accept(print), print.str()) + "В очереди " + std::to_string(database.room_size(i));
        ret.push_back(msg);
    }
    return ret;
}
bool MainController::user_in(int uid) {
    return (users_map.find(uid) != users_map.end());
}
void MainController::add_rule(const std::string &first, const std::string &second) {
    parser.input(first);
    auto left = parser.parse();
    parser.input(second);
    auto right = parser.parse();
    std::unique_ptr<Rule> tmp(new Rule{left, right});
    database.add_rule(tmp);
}