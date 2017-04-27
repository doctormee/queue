#include "User.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Specialist.h"
#include "Queue.h"

void add( std::vector<std::unique_ptr<User>> &vect, User* u ) {
    std::unique_ptr<User> s(u);
    vect.push_back(std::move(s));
}
/*
int main() {
    std::vector<std::unique_ptr<User>> vect;
    add(vect, (new User(1)));
    add(vect, (new User(2, "Ivan", "Ivanov", 10, 192, 70, 'F')));
    for (auto &user: vect) {
        std::cout << "UID: " << user->get_uid() << std::endl << "\t" << user->get_name() << " " << user->get_surname() << " is " << user->get_age() << " years old" << std::endl;
    }
    Specialist spec1;
    std::cout << spec1.get_name() << std::endl;
    spec1.add_service("Dentist");
    std::cout << spec1.get_service(0) << std::endl;
    try {
        std::cout << spec1.get_service(1) << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << ex.what() << std::endl;
    }
    spec1.add_service("Vet");
    try {
        for (auto i = 0; i < spec1.size(); ++i) {
            std::cout << spec1.get_service(i) << std::endl;
        }
    }
    Specialist spec2("Ivan", "Ivanov");
    spec2.add_service("Therapist");
    std::cout << spec2.get_name() << " " << spec2.get_surname() << " is a " << spec2.get_service(0) << std::endl;
    return 0;
}*///