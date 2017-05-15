#include "Queue.h"
#include "User.h"
#include "gtest/gtest.h"

TEST(Queue_test, Item_init_and_Push) {
    std::unique_ptr<User> new_user(new User{0});
    Queue my_queue;
    my_queue.push(new_user);
    ASSERT_EQ(new_user, nullptr);
} 
TEST(Queue_test, Queue_Remove) {
    std::unique_ptr<User> new_user(new User{0});
    Queue my_queue;
    my_queue.push(new_user);
    std::unique_ptr<User> new_user2(new User{2});
    my_queue.push(new_user2);
    my_queue.remove(2);
    ASSERT_EQ(my_queue.size(), 1);
    ASSERT_EQ(my_queue.begin() + 1, my_queue.end());
}
TEST(Queue_test, Queue_sort) {
    std::unique_ptr<User> new_user(new User{0});
    Queue my_queue;
    my_queue.push(new_user);
    std::unique_ptr<User> new_user2(new User{2});
    my_queue.push(new_user2);
    (*(my_queue.begin() + 1))->set_priority(2);
    my_queue.sort();
    ASSERT_EQ((*(my_queue.begin()))->user->get_uid(), 2);
}
TEST(Queue_test, Get_user) {
    std::unique_ptr<User> new_user(new User{0});
    Queue my_queue;
    my_queue.push(new_user);
    std::unique_ptr<User> new_user2(new User{2, "Ivan", "Ivanov", 10, 190, 72, 'M'});
    my_queue.push(new_user2);
    ASSERT_TRUE(my_queue.get_user(0).get_uid() == 0);
    ASSERT_TRUE(my_queue.get_user(2).get_weight() == 72);
    try {
        my_queue.get_user(3);
       FAIL();
    }
    catch (...) {
        //ok
    }
}