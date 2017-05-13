#include "User.h"
#include "gtest/gtest.h"
#include "Specialist.h"
#include "Evaluator.h"
#include <vector>
#include <stdexcept>
#include <string>

void add( std::vector<std::unique_ptr<User>> &vect, User* u ) {
    std::unique_ptr<User> s(u);
    vect.push_back(std::move(s));
}

TEST(User_Test, Initializing_Vector) {
    std::vector<std::unique_ptr<User>> vect;
    add(vect, (new User(1)));
    add(vect, (new User(2, "Ivan", "Ivanov", 10, 192, 70, 'F')));
    //ok
}
TEST(User_Test, Getters_Test) {
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
    //ok
}
TEST(Specialist_Test, Spec_init) {
    Specialist spec1;
    Specialist spec2("Ivan", "Ivanov");
    std::unique_ptr<Specialist> spec3(new Specialist());
}
TEST(Specialist_Test, Default_Getters) {
    Specialist spec1;
    ASSERT_STREQ(spec1.get_name().c_str(), "John");
    ASSERT_STRNE(spec1.get_surname().c_str(), "John");
}
TEST(Specialist_Test, Constructed_Getters) {
    Specialist spec1("Ivan", "John");
    ASSERT_STREQ(spec1.get_name().c_str(), "Ivan");
    ASSERT_STREQ(spec1.get_surname().c_str(), "John");
}
TEST(Specialist_Test, Services) {
    Specialist spec1;
    spec1.add_service("Dentist");
    ASSERT_STREQ(spec1.get_service(0).c_str(), "Dentist" );
    try {
        spec1.get_service(1);
        FAIL();
    }
    catch (std::out_of_range &ex) {
        //ok
    }
    spec1.add_service("Vet");
    try {
        for (auto i = 0; i < spec1.size(); ++i) {
            ASSERT_STRNE(spec1.get_service(i).c_str(), "");
        }
    }
    catch (...) {
        FAIL();//bad
    }
}

TEST(Specialist_Test, Trying_to_Evaluate) {
    Specialist spec1;
    Evaluator eval;
    try {
        spec1.accept(eval);
        FAIL();
    }
    catch (std::logic_error &ex) {
        //ok
    }
    catch (...) {
        FAIL();
    }
}