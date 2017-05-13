#include "UI.h"
#include "System.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>
#include <stdexcept>

TEST(UI_Test, Message) {
    UI ui;
    testing::internal::CaptureStdout();
    std::string expected = "Hello, World!";
    ui.msg(expected);
    std::string actual = testing::internal::GetCapturedStdout();
    expected += '\n';
    ASSERT_EQ(actual, expected);
}
TEST(UI_Test, Error) {
    UI ui;
    testing::internal::CaptureStdout();
    std::string expected = "All gone wrong!";
    ui.err(expected);
    std::string actual = testing::internal::GetCapturedStdout();
    expected = "Ошибка! All gone wrong!\n";
    ASSERT_EQ(actual, expected);
}


TEST(System_Test, Get_services) {
    UI ui;
    System main(&ui);
    ASSERT_THROW(main.get_services(), std::logic_error);
}

TEST(System_Test, No_ui) {
    System main;
    ASSERT_THROW(main.get_services(), std::logic_error);
}
TEST(System_Test, Add_user) {
    UI ui;
    System main(&ui);
    //main.add_user();
}