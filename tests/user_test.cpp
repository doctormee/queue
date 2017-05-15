#include "User.h"
#include "gtest/gtest.h"
#include "Specialist.h"
#include "Evaluator.h"
#include <vector>
#include <stdexcept>
#include <string>

void add( std::vector<std::unique_ptr<User>> &vect, User *u ) {
    std::unique_ptr<User> s(u);
    vect.push_back(std::move(s));
}

TEST(User_Test, Initializing_vector) {
    std::vector<std::unique_ptr<User>> vect;
    add(vect, (new User{1}));
    add(vect, (new User{2, "Ivan", "Ivanov", 10, 192, 70, 'F'}));
    ASSERT_EQ(vect.size(), 2);
    ASSERT_EQ(vect[0]->get_uid(), 1);
    ASSERT_EQ(vect[1]->get_uid(), 2);
}
TEST(User_Test, Getters) {
    std::vector<std::unique_ptr<User>> vect;
    add(vect, (new User{1}));
    add(vect, (new User{2, "Ivan", "Ivanov", 10, 192, 70, 'F'}));
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