#pragma once
#include <stack>
#include <map>
#include <string>
#include <vector>

#define MAX_USERS 10
#define MAX_ROOMS 10

class UI;
class Parser;
class DataController;
class System {
    DataController database;
    std::stack<int> free_uids;
    std::stack<int> free_rids;
    std::map<int, int> users_map;
    std::map<std::string, std::vector<int>> services_map;
    UI *interface;
    static Parser parser;
}