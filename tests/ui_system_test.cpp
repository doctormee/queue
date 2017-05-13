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
    System main(&ui);
    ui.attach(&main);
    ui.add_room();
}

TEST(System_Test, Get_services) {
    ConsoleUI ui;
    System main(&ui);
    ASSERT_THROW(main.get_services(), std::logic_error);
}

TEST(System_Test, No_ui) {
    System main;
    ASSERT_THROW(main.get_services(), std::logic_error);
}
/*
TEST(System_Test, Add_user) {
    ConsoleUI ui;
    System main(&ui);
    //main.add_user();
} */