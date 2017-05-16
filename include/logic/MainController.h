#pragma once
#include "DataController.h"
#include <stack>
#include <map>
#include <string>
#include <vector>

class Parser;

class MainController {
    DataController database;
    std::stack<int> free_uids;
    std::stack<int> free_rids;
    std::map<int, int> users_map;
    std::map<std::string, std::vector<int>> services_map;
    static Parser parser;

    int get_rid();
    int get_uid();
    void init();
public:
    static const int MAX_USERS;
    static const int MAX_ROOMS;
    MainController();
    std::vector<std::string> get_services();
    int add_user(std::string, std::string, std::string, int, int, int, char);
    void add_room(std::string, std::string, std::vector<std::string>);
    Queue &get_queue(int);
    void remove_user(int);
    void remove_room(int);
    std::vector<std::string> get_rooms();
    bool user_in(int);
    void add_rule(const std::string &, const std::string &);
    std::vector<std::string> get_rules();
};