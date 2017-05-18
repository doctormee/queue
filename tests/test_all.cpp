#include "gtest/gtest.h"
#include "MainController.h"
#include <iostream>
#include <fstream>
#include <cstdio>

int main(int argc, char **argv) {
    std::fstream rooms, rules;
    rooms.open(MainController::rooms_file_name, std::fstream::trunc);
    rules.open(MainController::rules_file_name, std::fstream::trunc);
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    if (rooms.is_open() && rules.is_open()) {
        std::string tmp;
        while (std::getline(rooms, tmp)) {
            rooms << tmp << std::endl;
        }
        while (std::getline(rules, tmp)) {
            rules << tmp << std::endl;
        }
    }
    return ret;
}
