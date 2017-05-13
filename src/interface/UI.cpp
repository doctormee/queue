#include "UI.h"

void UI::msg(std::string message) {
    std::cout << message << std::endl;
}
void UI::err(std::string error_message) {
    std::cout << "Ошибка! " << error_message << std::endl;
}

void UI::set_uid(int uid_) {
    uid = uid_;
}