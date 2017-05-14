#include "UI.h"
#include "System.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

UI::UI(): controller(nullptr) {}

UI::UI(System *src): controller(src) {}

void UI::attached() {
    if (controller == nullptr) {
        throw std::logic_error("Нет присоединённой системы!");
    }
}
void UI::attach(System *src) {
    controller = src;
}
void UI::set_uid(int uid_) {
    uid = uid_;
}
int UI::get_uid() {
    return uid;
}

void UI::add_room() {
    attached();
    std::string name, surname, buf;
    std::vector<std::string> services;
    try {
        msg("Введите имя специалиста: ");
        while (!inp(name) || name.empty()) {
            err("Некорректное имя!");
            msg("Введите имя специалиста: ");
        }
        msg("Введите фамилию специалиста: ");
        while (!inp(surname) || surname.empty()) {
            err("Некорректная фамилия!");
            msg("Введите фамилию специалиста: ");
        }
        msg("Введите услуги, оказываемые специалистом, по одной услуге на строку. В конце ввода введите строку end");
        inp(buf);
        while (buf != "end") {
            if (std::find(services.begin(), services.end(), buf) == services.end()) {
                services.push_back(buf);
            }
            inp(buf);
        }
        if (services.empty()) {
            err("Список услуг не может быть пустым!");
            return;
        }
        controller->add_room(name, surname, services);
    }
    catch (std::exception &ex) {
        err(ex.what());
        return;
    }
}

void UI::add_user() {
    attached();
    std::string name, surname, service;
    int age, height, weight;
    char gender;
    try {
        msg("Выберите услугу (или введите exit для выхода)");
        std::vector<std::string> services = controller->get_services();
        print_services();
        inp(service);
        while (std::find(services.begin(), services.end(), service) == services.end()) {
            if (service == "exit") {
                return;
            } else {
                if (service.empty()) {
                    return;
                }
                err("Нет такой услуги!");
                msg("Выберите услугу (или введите exit для выхода)");
                print_services();
                inp(service);
            }
        }
        msg("Введите имя");
        while (!inp(name) || name.empty()) {
            err("Некорректное имя!");
            msg("Введите имя");
        }
        msg("Введите фамилию");
        while (!inp(surname) || surname.empty()) {
            err("Некорректная фамилия!");
            msg("Введите фамилию");
        }
        msg("Введите свой возраст (в годах)");
        while (!inp(age) || (age < 0)) {
            err("Некорректный возраст!");
            msg("Введите свой возраст (в годах)");
        }
        msg("Введите свой рост (в см)");
        while (!inp(height) || (height < 0)) {
            err("Некорректный рост!");
            msg("Введите свой рост (в см)");
        }
        msg("Введите свой вес (в кг)");
        while (!inp(weight) || (weight < 0)) {
            err("Некорректный вес!");
            msg("Введите свой вес (в кг)");
        }
        msg("Введите пол (латинская M или F)");
        while (!inp(gender) || ((gender != 'M') && (gender != 'F'))) {
            err("Некорректный пол!");
            msg("Введите пол (латинская M или F)");
        }
        set_uid(controller->add_user(service, name, surname, age, height, weight, gender));
    }
    catch (std::exception &ex) {
        err(ex.what());
        return;
    }
}

void UI::print_services() {
    try {
        std::vector<std::string> services = controller->get_services();
        for (auto &i: services) {
            msg(i);
        }
    }
    catch (std::exception &ex) {
        err(ex.what());
    }
}

void UI::print_queue() {
    try {
        Queue &q = controller->get_queue(uid);
        std::string message = "Ваш идентификатор: " + std::to_string(uid);
        msg(message);
        int pos = 0;
        auto it = q.begin();
        for (auto i = 0; it != q.end(); ++i) {
            msg((*it)->user->get_name() + " " + (*it)->user->get_surname() + ". Идентификатор: " + std::to_string((*it)->user->get_uid()));
            if ((*it)->user->get_uid() == uid) {
                pos = i + 1;
            }
            ++it;
        }
        msg("Ваш номер в очереди: " + std::to_string(pos));
    }
    catch (std::exception &ex) {
        err(ex.what());
    }
}

void UI::print_rooms() {
    std::vector<std::string> buf = controller->get_rooms();
    for (auto i: buf) {
        msg(i);
    }
}