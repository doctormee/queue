#include "Queue.h"
#include "User.h"
#include "gtest/gtest.h"

TEST(Queue_test, Item_init_and_Push) {
    std::unique_ptr<User> new_user(new User(0));
    Queue my_queue;
    my_queue.push(new_user);
    ASSERT_EQ(new_user, nullptr);
} 
TEST(Queue_test, Queue_Remove) {
    std::unique_ptr<User> new_user(new User(0));
    Queue my_queue;
    my_queue.push(new_user);
    std::unique_ptr<User> new_user2(new User(2));
    my_queue.push(new_user2);
    my_queue.remove(2);
    ASSERT_EQ(my_queue.size(), 1);
    ASSERT_EQ(my_queue.begin() + 1, my_queue.end());
}
TEST(Queue_test, Queue_sort) {
    std::unique_ptr<User> new_user(new User(0));
    Queue my_queue;
    my_queue.push(new_user);
    std::unique_ptr<User> new_user2(new User(2));
    my_queue.push(new_user2);
    (*(my_queue.begin() + 1))->set_priority(2);
    my_queue.sort();
    ASSERT_EQ((*(my_queue.begin()))->user->get_uid(), 2);
}
/*
TEST(Rule_Test, getters_check) {
    Rule* r = new Rule(Field::AGE, Sign::LESS, 10, Field::AGE, Sign::MORE, 30);
    for (auto i = 1; i <= 2; ++i) {
        ASSERT_EQ(r->get_field(i), Field::AGE);
        ASSERT_NE(r->get_sign(i), Sign::NOTEQ);
        ASSERT_GE(r->get_value(i), 10);
    }
}
TEST(Rule_Test, invalid_getter_param) {
    Rule r(Field::ALL, Sign::LESS, 10, Field::AGE, Sign::MORE, 30);
    try {
        r.get_field(3);
        ASSERT_TRUE(0);
    }
    catch (std::out_of_range &ex) {
        //ok
    }
    try {
        r.get_sign(10);
        ASSERT_TRUE(0);
    }
    catch (std::out_of_range &ex) {
        //ok
    }
    try {
        r.get_value(0);
        ASSERT_TRUE(0);
    }
    catch (std::out_of_range &ex) {
        //ok
    }
}

*/