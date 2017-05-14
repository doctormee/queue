#include "StreamUI.h"
#include "System.h"
#include "gtest/gtest.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

TEST(System_Test, Empty_services) {
    System main;
    ASSERT_THROW(main.get_services(), std::logic_error);
}
TEST(System_Test, Get_services) {
    System main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    serv.push_back("Therapist");
    serv.push_back("Therapist");
    ASSERT_EQ(serv.size(), 3);
    main.add_room(name, surname, serv);
    ASSERT_NO_THROW(serv = main.get_services());
    ASSERT_EQ(serv.size(), 2);
}

TEST(System_Test, Add_user) {
    System main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    serv.push_back("Therapist");
    serv.push_back("Therapist");
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    ASSERT_EQ(main.get_queue(0).size(), 1);
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    ASSERT_EQ(main.get_queue(0).size(), 1);
    ASSERT_EQ(main.get_queue(1).size(), 1);
} 
TEST(System_Test, Remove_user) {
    System main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    serv.push_back("Therapist");
    serv.push_back("Therapist");
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    ASSERT_EQ(main.get_queue(0).size(), 1);
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    ASSERT_EQ(main.get_queue(0).size(), 1);
    ASSERT_EQ(main.get_queue(1).size(), 1);
    main.remove_user(1);
    main.remove_user(0);
    ASSERT_THROW(main.remove_user(0), std::logic_error);
    ASSERT_EQ(main.add_user(serv[0], name, surname, 10, 100, 60, 'F'), 0);
}

TEST(System_Test, Remove_room) {
    System main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    serv.push_back("Therapist");
    serv.push_back("Therapist");
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    ASSERT_THROW(main.remove_room(2), std::exception);
    main.remove_room(1);
    ASSERT_THROW(main.get_queue(1), std::exception);
    ASSERT_EQ(main.add_user(serv[0], name, surname, 10, 100, 60, 'F'), 1);
    ASSERT_EQ(main.get_queue(0).size(), 2);
    main.add_room(name, surname, serv);
    ASSERT_NO_THROW(main.get_queue(1));
}

TEST(System_Test, Get_rooms) {
    System main;
    ASSERT_EQ(main.get_rooms().size(), 0);
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    serv.push_back("Therapist");
    serv.push_back("Therapist");
    main.add_room(name, surname, serv);
    ASSERT_EQ(main.get_rooms().size(), 2);
}

TEST(System_Test, User_in) {
    System main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    serv.push_back("Therapist");
    serv.push_back("Therapist");
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    ASSERT_TRUE(main.user_in(0));
    ASSERT_FALSE(main.user_in(1));
}