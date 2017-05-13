#include "ConsoleUI.h"
#include "System.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

ConsoleUI::ConsoleUI(System *src): UI(src) {}

void ConsoleUI::msg(std::string message) {
    std::cout << message << std::endl;
}
void ConsoleUI::err(std::string error_message) {
    std::cout << "Ошибка! " << error_message << std::endl;
}
bool ConsoleUI::inp(std::string &to) {
    std::cin >> to;
    if (std::cin.eof()) {
        throw std::logic_error(ERR_MSG);
    }
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        return false;
    }
    else {
        return true;
    }
}

bool ConsoleUI::inp(int &to) {
    std::cin >> to;
    if (std::cin.eof()) {
        throw std::logic_error(ERR_MSG);
    }
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        return false;
    }
    else {
        return true;
    }
}

bool ConsoleUI::inp(char &to) {
    std::cin >> to;
    if (std::cin.eof()) {
        throw std::logic_error(ERR_MSG);
    }
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        return false;
    }
    else {
        return true;
    }
}
/*
void ConsoleUI::add_room() {
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

void ConsoleUI::get_services() {
    msg
}*/