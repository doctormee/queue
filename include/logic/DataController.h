#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
class Rule;
class Constants;
class User;
class Queue;
class Specialist;
class DataController {
    struct Room {
        int rid;
        std::unique_ptr<Specialist> specialist;
        std::unique_ptr<Queue> queue;
        Room(int, std::unique_ptr<Specialist> &);
        };
    std::map<int, std::unique_ptr<Room>> rooms;
    std::vector<std::unique_ptr<Rule>> rules;
public:
    ~DataController() = default;
    void add_room(int, std::string, std::string, std::vector<std::string>);
    void delete_room(int);
    Specialist &get_specialist(int);
    void add_user(int, int, std::string, std::string, int, int, int, char);
    void add_user(int, std::unique_ptr<User> &);
    void delete_user(int, int);
    Queue &get_queue(int); 
    void add_rule(std::unique_ptr<Rule> &);
    void delete_rule(int);
    int matching_rules(User &, User &) const;
    void update_room(int);
    void update_all();
};
