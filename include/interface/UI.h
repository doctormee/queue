#pragma once
#include <string>
class MainController;
class UI {
    int uid;
    MainController *controller;
protected:
    void attached();
public:
    UI();
    UI(MainController *);
    void attach(MainController *);
    virtual void msg(std::string) = 0;
    virtual void err(std::string) = 0;
    virtual bool inp(std::string &) = 0;
    virtual bool inp(int &) = 0;
    virtual bool inp(char &) = 0;
    virtual void ignore() = 0;
    void set_uid(int);
    int get_uid();
    void add_room();
    bool add_user();
    void add_rule();
    void remove_room();
    void remove_rule();
    void print_services(); 
    void print_queue();
    void print_rooms();
    void print_rules();
    void logout();
    bool login(int);
    void save();
};