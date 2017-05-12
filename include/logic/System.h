#pragma once
#include <stack>
#include <map>
#include <string>
#include <vector>

class DataController;
class System {
    DataController database;
    std::stack<int> free_uids;
    std::map<int, int> users_map;
    std::map<std::string, std::vector<int>> services_map;
}