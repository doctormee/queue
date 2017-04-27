#include "User.h"
#include "gtest/gtest.h"
#include <vector>
#include <string>

void add( std::vector<std::unique_ptr<User>> &vect, User* u ) {
    std::unique_ptr<User> s(u);
    vect.push_back(std::move(s));
}

TEST(User_Test, Initializing_vector) {
    std::vector<std::unique_ptr<User>> vect;
    add(vect, (new User(1)));
    add(vect, (new User(2, "Ivan", "Ivanov", 10, 192, 70, 'F')));
    ASSERT_EQ(vect[0]->get_uid(), 1);
    ASSERT_NE(vect[1]->get_uid(), 1);
    ASSERT_STREQ((vect[0]->get_name()).c_str(),"John");
    ASSERT_STRNE((vect[1]->get_surname()).c_str(), "IvAnOV");
    ASSERT_LT(vect[0]->get_age(), 50);
    ASSERT_TRUE(vect[0]->get_height());
    ASSERT_EQ(vect[1]->get_gender(), 'F');
    ASSERT_GT(vect[1]->get_weight(), 69);
}
    /*Specialist spec1;
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