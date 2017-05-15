#include "StreamUI.h"
#include "MainController.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

StreamUI::StreamUI(
    std::istream &inp, 
    std::ostream &out)
    : input_stream{inp}, output_stream{out}
{
}

StreamUI::StreamUI(
    std::istream &inp, 
    std::ostream &out, 
    MainController *src)
    : UI{src}, input_stream{inp}, output_stream{out}
{
}

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
