#include "UI.h"
#include "System.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

void UI::attached() {
    if (database == nullptr) {
        throw std::logic_error("Нет присоединённой системы!");
    }
}
void UI::attach(System *src) {
    database = src;
}
void UI::set_uid(int uid_) {
    uid = uid_;
}

void UI::add_room() {
    attached();
    std::string name, surname, buf;
    std::vector<std::string> services;
    msg("Введите имя специалиста: ");
    if (!inp(name)) {
        err("Некорректное имя!");
        return;
    }
    msg("Введите фамилию специалиста: ");
    if (!inp(surname)) {
        err("Некорректная фамилия!");
        return;
    }
    msg("Введите услуги, оказываемые специалистом, по одной услуге на строку. В конце ввода введите строку end");
    inp(buf);
    while ((buf != "end") && (!buf.empty())) {
        if (std::find(services.begin(), services.end(), buf) == services.end()) {
            services.push_back(buf);
        }
        inp(buf);
    }
    if (services.empty()) {
        err("Список услуг не может быть пустым!");
        return;
    }
    try {
        database->add_room(name, surname, services);
    }
    catch (std::exception &ex) {
        err(ex.what());
        return;
    }
}
/*
void UI::get_services() {
    msg
}*/