#pragma once
#include <string>
#include "UI.h"
class System;

class ConsoleUI: public UI {
    const std::string ERR_MSG = "Неожиданный конец ввода!";
public:
    ConsoleUI() = default;
    ConsoleUI(System *);
    void msg(std::string) override;
    void err(std::string) override;
    bool inp(std::string &) override;
    bool inp(int &) override;
    bool inp(char &) override;
};