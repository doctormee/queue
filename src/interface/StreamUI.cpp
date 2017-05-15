#include "StreamUI.h"
#include "MainController.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

StreamUI::StreamUI(std::istream &inp, std::ostream &out): input_stream(inp), output_stream(out) {}

StreamUI::StreamUI(std::istream &inp, std::ostream &out, MainController *src): UI(src), input_stream(inp), output_stream(out) {}

void StreamUI::msg(std::string message) {
    output_stream << message << std::endl;
}
void StreamUI::err(std::string error_message) {
    output_stream << "Ошибка! " << error_message << std::endl;
}
bool StreamUI::inp(std::string &to) {
    std::getline(input_stream, to, '\n');
    if (input_stream.eof()) {
        throw std::logic_error(ERR_MSG);
    }
    if (!input_stream) {
        input_stream.clear();
        input_stream.ignore(10000,'\n');
        return false;
    }
    else {
        return true;
    }
}

bool StreamUI::inp(int &to) {
    input_stream >> to;
    if (input_stream.eof()) {
        throw std::logic_error(ERR_MSG);
    }
    if (!input_stream) {
        input_stream.clear();
        input_stream.ignore(10000,'\n');
        return false;
    }
    else {
        return true;
    }
}

bool StreamUI::inp(char &to) {
    input_stream >> to;
    if (input_stream.eof()) {
        throw std::logic_error(ERR_MSG);
    }
    if (!input_stream) {
        input_stream.clear();
        input_stream.ignore(10000,'\n');
        return false;
    }
    else {
        return true;
    }
}
std::istream &StreamUI::get_istream() {
    return input_stream;
}

std::ostream &StreamUI::get_ostream() {
    return output_stream;
}
void StreamUI::add_rule() {
    attached();
    
}

/*
void StreamUI::add_room() {
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

void StreamUI::get_services() {
    msg
}*/