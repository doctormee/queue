#pragma once
#include <string>
#include "UI.h"
class System;

class ConsoleUI: public UI {
    int uid;
    System *database;
public:
    ConsoleUI() = default;
    ConsoleUI(System *);
    void msg(std::string) override;
    void err(std::string) override;
    bool inp(std::string &) override;
    bool inp(int &) override;
    bool inp(char &) override;
};