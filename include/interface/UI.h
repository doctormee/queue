#pragma once
#include <iostream>
#include <string>

class UI {
    int uid;
public:
    void msg(std::string);
    void err(std::string);
    void set_uid(int);
};