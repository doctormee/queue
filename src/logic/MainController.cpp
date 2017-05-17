#include "MainController.h"
#include "UI.h"
#include "Parser.h"
#include "Rule.h"
#include "Printer.h"
#include "Predicate.h"
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
        for (auto const &service: services_map) {
            ret.push_back(service.first);
        }
        return ret;
    }
}

int MainController::add_user(
    std::string service, 
    std::string name, 
    std::string surname, 
    int age, 
    int height, 
    int weight, 
    char gender)
{
    int rid, uid;
    uid = get_uid();
    auto req_service = services_map.find(service);
    //поиск комнаты с наименьшей очередью
    rid = req_service->second[0];
    for (auto &current_rid: req_service->second) {
        if (database.room_size(current_rid) < database.room_size(rid)) {
            rid = current_rid;
        }
    }
    database.add_user(rid, uid, name, surname, age, height, weight, gender);
    users_map[uid] = rid;
    return uid;
}

void MainController::add_room(
    std::string name, 
    std::string surname, 
    std::vector<std::string> services)
{
    int rid;
    rid = get_rid();
    database.add_room(rid, name, surname, services);
    for (auto const &service: services) {
        services_map[service].push_back(rid);
    }
}

Queue &MainController::get_queue(int uid) {
    auto record = users_map.find(uid);
    if (record == users_map.end()) {
        throw std::logic_error("Пользователь не существует!");
    }
    auto rid = record->second;
    return database.get_queue(rid);
}

void MainController::remove_user(int uid) {
    auto record = users_map.find(uid);
    if (record == users_map.end()) {
        throw std::logic_error("Пользователь не существует!");
    }
    auto rid = record->second;
    database.delete_user(rid, uid);
    free_uids.push(uid);
    users_map.erase(uid);
}
void MainController::remove_room(int rid) {  
    std::vector<int> users_to_remove;  
    for (auto const &record: users_map) {    
        if (record.second == rid) {
            users_to_remove.push_back(record.first);
        }
    }    
    for (auto &user: users_to_remove) {
        remove_user(user);
    }
    auto &spec = database.get_specialist(rid);
    for (int i = 0; i < spec.size(); ++i) {
        std::string current = spec.get_service(i);
        services_map[current].erase(std::find(services_map[current].begin(), services_map[current].end(), rid));
    }
    database.delete_room(rid);
    free_rids.push(rid);
}
std::vector<std::string> MainController::get_rooms() {
    std::vector<std::string> ret;
    std::string msg;
    std::set<int> rids;
    for (auto const &record: services_map) {
        for (auto const &rid: record.second) {
            if (rids.find(rid) == rids.end()) {
                rids.insert(rid);
            }
        }
    }
    Printer print;
    for (auto rid: rids) {
        print.flush();
        Specialist &spec = database.get_specialist(rid);
        msg = std::to_string(rid) + ". " + (spec.accept(print), print.str());
        msg += "В очереди " + std::to_string(database.room_size(rid));
        ret.push_back(msg);
    }
    return ret;
}
bool MainController::user_in(int uid) {
    return (users_map.find(uid) != users_map.end());
}
void MainController::add_rule(
    const std::string &first, 
    const std::string &second)
{
    parser.input(first);
    auto left = parser.parse();
    parser.input(second);
    auto right = parser.parse();
    std::unique_ptr<Rule> tmp{new Rule{left, right}};
    database.add_rule(tmp);
}
std::vector<std::string> MainController::get_rules() {
    std::vector<std::string> ret;
    Printer print;
    std::string tmp;
    int number = 0;
    auto rules_list = database.get_rules();
    if (rules_list.size() == 0) {
        return ret;
    }
    for (auto const &rule: rules_list) {
        ++number;
        print.flush();
        rule->get_first()->accept(print);
        tmp = std::to_string(number);
        tmp += ". Prioritize " + print.str();
        print.flush();
        rule->get_second()->accept(print);
        tmp += " over " + print.str();
        ret.push_back(tmp);
    }
    return ret;
}

void MainController::remove_rule(int rule_number) {
    database.delete_rule(rule_number - 1);
}