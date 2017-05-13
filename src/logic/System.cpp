#include "System.h"
#include "UI.h"
#include "Parser.h"
#include "DataController.h"
#include <stdexcept>
#include <iostream>

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
