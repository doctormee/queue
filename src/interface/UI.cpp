#include "UI.h"
#include "MainController.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

UI::UI()
    : controller{nullptr} 
{
}

UI::UI(MainController *src)
    : controller{src} 
{
}

void UI::attached() {
    if (controller == nullptr) {
        throw std::logic_error("Нет присоединённой системы!");
    }
}
void UI::attach(MainController *src) {
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
    } catch (std::exception &ex) {
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
    } catch (std::exception &ex) {
        err(ex.what());
        return;
    }
}
void UI::remove_room() {
    attached();
    try {
        int rid;
        msg("Выберите удаляемого специалиста, введите его номер и нажмите enter: ");
        print_rooms();
        inp(rid);
        controller->remove_room(rid);
        msg("Специалист удалён!");
    } catch (std::exception &ex) {
        err(ex.what());
    }
}


void UI::print_services() {
    attached();
    try {
        std::vector<std::string> services = controller->get_services();
        for (auto &i: services) {
            msg(i);
        }
    } catch (std::exception &ex) {
        err(ex.what());
    }
}

void UI::print_queue() {
    attached();
    try {
        auto queue = controller->get_queue(uid);
        std::string message = "Ваш идентификатор: " + std::to_string(uid);
        msg(message);
        for (auto &user: queue) {
            msg(user);
        }
    } catch (std::exception &ex) {
        err(ex.what());
    }
}

void UI::print_rooms() {
    attached();
    try {
        std::vector<std::string> buf = controller->get_rooms();
        for (auto i: buf) {
            msg(i);
        }
    } catch (std::exception &ex) {
        err(ex.what());
        return;
    }
}

void UI::print_rules() {
    attached();
    try {
        auto rules = controller->get_rules();
        if (rules.empty()) {
            msg("Нет правил определения приоритета!");
            return;
        }
        for (auto &i: rules) {
            msg(i);
        }
    } catch (std::exception &ex) {
        err(ex.what());
    }
}

void UI::logout() {
    attached();
    try {
        controller->remove_user(uid);
    } catch (std::exception &ex) {
        err(ex.what());
    }
}
bool UI::login(int uid_) {
    attached();
    if (controller->user_in(uid_)) {
        set_uid(uid_);
        return true;
    }
    err("Нет такого пользователя!");
    return false;
}
void UI::add_rule() {
    attached();
    try {
        std::string left, right;
        msg("Введите левое условие (корректное выражение на языке логических выражений) и нажмите enter: ");
        inp(left);
        msg("Введите правое условие (корректное выражение на языке логических выражений) и нажмите enter: ");
        inp(right);
        controller->add_rule(left, right);
    } catch (std::exception &ex) {
        err(ex.what());
    }
}
void UI::remove_rule() {
    attached();
    try {
        int rule_number;
        msg("Выберите удаляемое правило, введите его номер и нажмите enter: ");
        print_rules();
        inp(rule_number);
        controller->remove_rule(rule_number);
        msg("Правило удалено!");
    } catch (std::exception &ex) {
        err(ex.what());
    }
}
