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
        ignore();
        input_stream.clear();
        return false;
    } else if (to.empty() || (to.find_first_not_of(' ') == to.npos)) {
        return false;
    } else {
        return true;
    }
}

bool StreamUI::inp(int &to) {
    std::string tmp;
    if (!inp(tmp) || (tmp.find_first_of(' ') != tmp.npos)) {
        return false;
    }
    try {
        to = stoi(tmp);
        return true;
    } catch (...) {
        return false;
    }
}
void StreamUI::ignore() {
    input_stream.ignore(std::string{}.max_size(),'\n');
}
bool StreamUI::inp(char &to) {
    std::string tmp;
    if (!inp(tmp)) {
        return false;
    }
    if (tmp.size() != 1) {
        return false;
    }
    to = tmp[0];
    return true;
}
