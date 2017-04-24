#include <User.h>
#include <iostream>
#include <vector>
#include <memory>

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
    return 0;
}