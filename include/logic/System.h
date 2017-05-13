#pragma once
#include "DataController.h"
#include <stack>
#include <map>
#include <string>
#include <vector>

class UI;

class Parser;

class System {
    const int MAX_USERS = 10;
    const int MAX_ROOMS = 10;
    
    DataController database;
    std::stack<int> free_uids;
    std::stack<int> free_rids;
    std::map<int, int> users_map;
    std::map<std::string, std::vector<int>> services_map;
    UI *interface;
    static Parser parser;
    
    void attached();
    int get_rid();
    int get_uid();
    void init();
public:
    System();
    System(UI *);
    void get_services();
    void add_user();
    void add_room(std::string, std::string, std::vector<std::string>);
};