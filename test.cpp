#include <User.h>
#include <iostream>
#include <vector>
#include <memory>
#include <Specialist.h>

void add( std::vector<std::shared_ptr<User>> &vect, User* u ) {
    std::shared_ptr<User> s(u);
    vect.push_back(s);
}

int main() {
    std::vector<std::shared_ptr<User>> vect;
    add(vect, (new User(1)));
    add(vect, (new User(2, "Ivan", "Ivanov", 10, 192, 70, 'F')));
    for (auto user: vect) {
        std::cout << "UID: " << user->get_uid() << std::endl << "\t" << user->get_name() << " " << user->get_surname() << " is " << user->get_age() << " years old" << std::endl;
    }
    Specialist spec1;
    std::cout << spec1.get_name() << std::endl;
    spec1.add_service("blowjob");
    std::cout << spec1.get_service(0) << std::endl;
    try {
        std::cout << spec1.get_service(1) << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << ex.what() << std::endl;
    }
    Specialist spec2("Ivan", "Ivanov");
    spec2.add_service("Therapist");
    std::cout << spec2.get_name() << " " << spec2.get_surname() << " is a " << spec2.get_service(0) << std::endl;
    return 0;
}