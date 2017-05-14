#pragma once
#include <string>
class System;
class UI {
    int uid;
    System *controller;
    void attached();
public:
    UI();
    UI(System *);
    void attach(System *);
    virtual void msg(std::string) = 0;
    virtual void err(std::string) = 0;
    virtual bool inp(std::string &) = 0;
    virtual bool inp(int &) = 0;
    virtual bool inp(char &) = 0;   
    void set_uid(int);
    int get_uid();
    void add_room();
    void add_user();
    void print_services(); 
    void print_queue();
    void print_rooms();
};