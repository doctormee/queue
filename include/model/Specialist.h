#pragma once
#include <string>
#include <vector>
#include "Visitable.h"
class Visitor;
class Specialist: public Visitable {
    std::string name, surname;
    std::vector<std::string> services;
public:
    Specialist();
    Specialist(std::string, std::string);
    std::string get_name() const;
    std::string get_surname() const;
    void add_service(std::string);
    std::string get_service(int) const;
    int size() const;
    void accept(Visitor &) override;
};
