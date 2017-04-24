#ifndef SPECIALIST_H
#define SPECIALIST_H
#include <string>
#include <vector>
class Specialist {
    std::string name, surname;
    std::vector<std::string> services;
public:
    Specialist();
    Specialist(std::string, std::string);
    std::string get_name() const;
    std::string get_surname() const;
    void add_service(std::string);
    std::string get_service(int);
    int size();
};
#endif