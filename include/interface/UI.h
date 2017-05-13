#pragma once
#include <string>
class System;
class UI {
    int uid;
    System *database;
    void attached();
public:
    void attach(System *);
    virtual void msg(std::string) = 0;
    virtual void err(std::string) = 0;
    virtual bool inp(std::string &) = 0;
    virtual bool inp(int &) = 0;
    virtual bool inp(char &) = 0;   
    void set_uid(int);
    void add_room();
    void get_services(); 
};