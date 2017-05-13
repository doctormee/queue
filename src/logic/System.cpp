#include "System.h"
#include "UI.h"
#include "Parser.h"
#include "DataController.h"
#include <stdexcept>
#include <iostream>

void System::attached() {
    if (!interface) {
        throw std::logic_error("Нет интерфейса");
    }
}

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

System::System(): interface(nullptr) {
    init();
}


System::System(UI *ui): interface(ui) {
    init();
}

void System::get_services() {
    attached();
    if (services_map.size() == 0) {
        throw std::logic_error("Нет доступных услуг!");
    }
    else {
        for (auto &i: services_map) {
            interface->msg(i.first);
        }
    }
}

void System::add_user() {
    attached();
    std::string name, surname, service;
    int age, height, weight, rid, uid;
    char gender;
    try {
        uid = get_uid();
        interface->msg("Выберите услугу (или введите exit для выхода)");
    }
    catch (std::exception &ex) {
        interface->err(ex.what());
        return;
    }
    std::cin >> service;
    if (service == "exit") {
        return;
    }
    auto it = services_map.find(service);
    if (it == services_map.end()) {
        interface->err("Нет такой услуги!");
        return;
    }
    
    //поиск комнаты с наименьшей очередью
    rid = it->second[0];
    for (auto j: it->second) {
        if (database.room_size(j) < database.room_size(rid)) {
            rid = j;
        }
    }
    interface->msg("Введите имя");
    std::cin >> name;
    if (!std::cin) {
        interface->err("Некорректное имя!");
        return;
    }
    interface->msg("Введите фамилию");
    std::cin >> surname;
    if (!std::cin) {
        interface->err("Некорректная фамилия!");
        return;
    }
    interface->msg("Введите свой возраст (в годах)");
    std::cin >> age;
    if (!std::cin || (age < 0)) {
        interface->err("Некорректный возраст!");
        return;
    }
    interface->msg("Введите свой рост (в см)");
    std::cin >> height;
    if (!std::cin || (height < 0)) {
        interface->err("Некорректный рост!");
        return;
    }
    interface->msg("Введите свой вес (в кг)");
    std::cin >> weight;
    if (!std::cin || (weight < 0)) {
        interface->err("Некорректный вес!");
        return;
    }
    interface->msg("Введите пол (латинская M или F)");
    std::cin >> gender;
    if (!std::cin || ((gender != 'M') && (gender != 'F'))) {
        interface->err("Некорректный пол!");
        return;
    }
    
}

void System::add_room(std::string name, std::string surname, std::vector<std::string> services) {
    int rid;
    rid = get_rid();
    database.add_room(rid, name, surname, services);
    for (auto &i: services) {
        services_map[i].push_back(rid);
    }
}
