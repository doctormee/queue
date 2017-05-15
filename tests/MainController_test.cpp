#include "StreamUI.h"
#include "MainController.h"
#include "gtest/gtest.h"
#include "ParseException.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

TEST(MainController_Test, Empty_services) {
    MainController main;
    ASSERT_THROW(main.get_services(), std::logic_error);
}
TEST(MainController_Test, Get_services) {
    MainController main;
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

TEST(MainController_Test, Add_room) {
    MainController main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    serv.push_back("Therapist");
    ASSERT_NO_THROW(main.add_room(name, surname, serv));
}


TEST(MainController_Test, Add_room_overflow) {
    MainController main;
    std::string name, surname, service;
    std::vector<std::string> services;
    name = "Ivan";
    surname = "Ivanov";
    service = "Dentist";
    for (auto i = 1; i <= MainController::MAX_ROOMS; ++i) {
        service += "1";
        services.push_back(service);
        ASSERT_NO_THROW(main.add_room(name, surname, services));
        ASSERT_NO_THROW(main.add_user(services[i - 1], name, surname, 10, 100, 60, 'F'));
    }
    ASSERT_THROW(main.add_room(name, surname, services), std::out_of_range);
} 

TEST(MainController_Test, Add_user) {
    MainController main;
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

TEST(MainController_Test, Add_user_overflow) {
    MainController main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    serv.push_back("Therapist");
    serv.push_back("Therapist");
    main.add_room(name, surname, serv);
    for (auto i = 1; i <= MainController::MAX_USERS; ++i) {
        ASSERT_NO_THROW(main.add_user(serv[1], name, surname, 10, 100, 60, 'F'));
        ASSERT_EQ(main.get_queue(0).size(), i);
    }
    ASSERT_THROW(main.add_user(serv[1], name, surname, 10, 100, 60, 'F'), std::out_of_range);
    ASSERT_THROW(main.add_user(serv[0], name, surname, 10, 100, 60, 'F'), std::out_of_range);
    ASSERT_EQ(main.get_queue(0).size(), MainController::MAX_USERS);
} 
TEST(MainController_Test, Remove_user) {
    MainController main;
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

TEST(MainController_Test, Remove_room) {
    MainController main;
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

TEST(MainController_Test, Get_rooms) {
    MainController main;
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

TEST(MainController_Test, User_in) {
    MainController main;
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
TEST(MainController_Test, Add_rule) {
    MainController main;
    std::string first, second, first_exp, second_exp;
    first_exp = "ALL ";
    first = first_exp;
    second_exp = "(gender = F)";
    second = second_exp;
    ASSERT_NO_THROW(main.add_rule(first, second));
    ASSERT_EQ(first, first_exp);
    ASSERT_EQ(second, second_exp);
    ASSERT_THROW(main.add_rule("", "ALL "), ParseException);
    ASSERT_THROW(main.add_rule("ALL ", "gender > M"), ParseException);
}