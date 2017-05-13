#include "ConsoleUI.h"
#include "System.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>
#include <stdexcept>

TEST(ConsoleUI_Test, Message) {
    ConsoleUI ui;
    testing::internal::CaptureStdout();
    std::string expected = "Hello, World!";
    ui.msg(expected);
    std::string actual = testing::internal::GetCapturedStdout();
    expected += '\n';
    ASSERT_EQ(actual, expected);
}
TEST(ConsoleUI_Test, Error) {
    ConsoleUI ui;
    testing::internal::CaptureStdout();
    std::string expected = "All gone wrong!";
    ui.err(expected);
    std::string actual = testing::internal::GetCapturedStdout();
    expected = "Ошибка! All gone wrong!\n";
    ASSERT_EQ(actual, expected);
}

TEST(ConsoleUI_Test, Add_room) {
    ConsoleUI ui;
    System main;
    ui.attach(&main);
    ui.add_room();
}
TEST(ConsoleUI_Test, Add_user) {
    ConsoleUI ui;
    System main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Дантист");
    main.add_room(name, surname, serv);
    ui.attach(&main);
    ui.set_uid(1);
    ui.add_user();
    ASSERT_EQ(ui.get_uid(), 0);
}


TEST(ConsoleUI_Test, Print_services) {
    System main;
    ConsoleUI ui(&main);
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    testing::internal::CaptureStdout();
    ui.print_services();
    std::string actual = testing::internal::GetCapturedStdout();
    std::string expected = "Dentist\n";
    ASSERT_EQ(actual, expected);
}

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
    ConsoleUI ui;
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
} 