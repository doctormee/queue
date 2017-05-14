#include "System.h"
#include "UI.h"
#include "Parser.h"
#include "DataController.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <set>

int System::get_rid() {
    if (free_rids.size() == 0) {
        throw std::out_of_range("Нельзя добавить больше специалистов!");
    }
    else {
        int tmp = free_rids.top();
        free_rids.pop();
        return tmp;
    }
}

int System::get_uid() {
    if (free_uids.size() == 0) {
        throw std::out_of_range("Нельзя добавить больше пользователей!");
    }
    else {
        int tmp = free_uids.top();
        free_uids.pop();
        return tmp;
    }
}

void System::init() {
    int i;
    for (i = (MAX_USERS - 1); i >= 0; --i) {
        free_uids.push(i);
    }
    for (i = (MAX_ROOMS - 1); i >= 0; --i) {
        free_rids.push(i);
        
    }
}

System::System() {
    init();
}

std::vector<std::string> System::get_services() {
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

int System::add_user(std::string service, std::string name, std::string surname, int age, int height, int weight, char gender) {
    int rid, uid;
    uid = get_uid();
    auto it = services_map.find(service);
    //поиск комнаты с наименьшей очередью
    rid = it->second[0];
    for (auto j: it->second) {
        if (database.room_size(j) < database.room_size(rid)) {
            rid = j;
        }
    }
    database.add_user(rid, uid, name, surname, age, height, weight, gender);
    users_map[uid] = rid;
    return uid;
}

void System::add_room(std::string name, std::string surname, std::vector<std::string> services) {
    int rid;
    rid = get_rid();
    database.add_room(rid, name, surname, services);
    for (auto &i: services) {
        services_map[i].push_back(rid);
    }
}

Queue &System::get_queue(int uid) {
    auto it = users_map.find(uid);
    if (it == users_map.end()) {
        throw std::logic_error("Пользователь не существует!");
    }
    auto rid = it->second;
    return database.get_queue(rid);
}

void System::remove_user(int uid) {
    auto it = users_map.find(uid);
    if (it == users_map.end()) {
        throw std::logic_error("Пользователь не существует!");
    }
    auto rid = it->second;
    database.delete_user(rid, uid);
    free_uids.push(uid);
    users_map.erase(uid);
}
void System::remove_room(int rid) {
    for (auto i: users_map) {
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
std::vector<std::string> System::get_rooms() {
    std::vector<std::string> ret;
    std::string msg;
    std::set<int> rids;
    for (auto i: services_map) {
        for (auto j: i.second) {
            if (rids.find(j) == rids.end()) {
                rids.insert(j);
            }
        }
    }
    for (auto i: rids) {
        msg.clear();
        Specialist &spec = database.get_specialist(i);
        msg = std::to_string(i) + ". " + spec.get_name() + " " + spec.get_surname() + ". В очереди " + std::to_string(database.room_size(i)) + ". Услуги: ";
        for (auto j = 0; j < spec.size(); ++j) {
            msg += spec.get_service(j) + " ";
        }
        ret.push_back(msg);
    }
    return ret;
}

bool System::user_in(int uid) {
    return (users_map.find(uid) != users_map.end());
}