#include "StreamUI.h"
#include "MainController.h"
#include "ParseException.h"
#include "gtest/gtest.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdio>

class StreamUI_Test: public ::testing::Test {
protected:
    std::ifstream inp_rooms, inp_rules;
    std::ofstream out_rooms, out_rules;
    virtual void SetUp() {
        out_rooms.open(".roomstmp.txt", std::fstream::trunc);
        out_rules.open(".rulestmp.txt", std::fstream::trunc);
        inp_rooms.open(MainController::rooms_file_name);
        inp_rules.open(MainController::rules_file_name);
        std::string tmp;
        while (std::getline(inp_rooms, tmp)) {
          out_rooms << tmp << std::endl;
        }
        while (std::getline(inp_rules, tmp)) {
          out_rules << tmp << std::endl;
        }
        out_rules.close();
        out_rooms.close();
        if (!inp_rooms.is_open() && !inp_rules.is_open()) {
            remove(".rulestmp.txt");
            remove(".roomstmp.txt");
        }
        remove(MainController::rooms_file_name.c_str());
        remove(MainController::rules_file_name.c_str());
        inp_rules.close();
        inp_rooms.close();
    }

    virtual void TearDown() {
        inp_rooms.open(".roomstmp.txt");
        inp_rules.open(".rulestmp.txt");
        out_rooms.open(MainController::rooms_file_name, std::fstream::trunc);
        out_rules.open(MainController::rules_file_name, std::fstream::trunc);
        std::string tmp;
        while (std::getline(inp_rooms, tmp)) {
           out_rooms << tmp << std::endl;
        }
        while (std::getline(inp_rules, tmp)) {
           out_rules << tmp << std::endl;
        }
        out_rules.close();
        out_rooms.close();
        inp_rules.close();
        inp_rooms.close();
        remove(".rulestmp.txt");
        remove(".roomstmp.txt");
    }
};

TEST_F(StreamUI_Test, Message) {
    std::stringstream inp, out;
    StreamUI ui{inp, out};
    std::string expected = "Hello, World!";
    ui.msg(expected);
    std::string actual;
    std::getline(out, actual);
    ASSERT_EQ(actual, expected);
}
TEST_F(StreamUI_Test, Error) {
    std::stringstream inp, out;
    StreamUI ui{inp, out};
    std::string expected = "All gone wrong!";
    ui.err(expected);
    std::string actual;
    std::getline(out, actual);
    expected = "Ошибка! All gone wrong!";
    ASSERT_EQ(actual, expected);
}

TEST_F(StreamUI_Test, Add_room) {
    std::stringstream inp, out;
    std::string actual, expected, empty;
    empty.clear();
    StreamUI ui{inp, out};
    MainController main;
    ui.attach(&main);
    inp << empty << std::endl << "John" << std::endl << empty << std::endl << "Appleseed" << std::endl << "Dental" << std::endl << "Therapist" << std::endl << "end" << std::endl;
    ui.add_room();
    expected = "Введите имя специалиста: \nОшибка! Некорректное имя!\nВведите имя специалиста: \nВведите фамилию специалиста: \nОшибка! Некорректная фамилия!\nВведите фамилию специалиста: \nВведите услуги, оказываемые специалистом, по одной услуге на строку. В конце ввода введите строку end\n";
    actual = out.str();
    ASSERT_EQ(actual, expected);
}
TEST_F(StreamUI_Test, Add_user) {
    std::stringstream inp, out;
    StreamUI ui{inp, out};
    MainController main;
    std::string name, surname, actual, expected, empty;
    empty.clear();
    std::vector<std::string> serv;
    name = "Иван";
    surname = "Иванов";
    serv.push_back("Дантист");
    main.add_room(name, surname, serv);
    ui.attach(&main);
    ui.set_uid(1);
    inp << 1 << std::endl << "Дантист" << std::endl;
    inp << empty << std::endl << "Иван" << std::endl;
    inp << empty << std::endl << "Иванов" << std::endl;
    inp << "1 " << std::endl << 1 << std::endl;
    inp << "   " << std::endl << 2 << std::endl;
    inp << "as" << std::endl << 3 << std::endl;
    inp << 10 << std::endl << 'a' << std::endl;
    inp << empty << std::endl << 'M'<< std::endl;
    expected = "Выберите услугу (или введите exit для выхода)\nДантист\nОшибка! Нет такой услуги!\nВыберите услугу (или введите exit для выхода)\nДантист\nВведите имя\nОшибка! Некорректное имя!\nВведите имя\nВведите фамилию\nОшибка! Некорректная фамилия!\nВведите фамилию\nВведите свой возраст (в годах)\nОшибка! Некорректный возраст!\nВведите свой возраст (в годах)\nВведите свой рост (в см)\nОшибка! Некорректный рост!\nВведите свой рост (в см)\nВведите свой вес (в кг)\nОшибка! Некорректный вес!\nВведите свой вес (в кг)\nВведите пол (латинская M или F)\nОшибка! Некорректный пол!\nВведите пол (латинская M или F)\nОшибка! Некорректный пол!\nВведите пол (латинская M или F)\nОшибка! Некорректный пол!\nВведите пол (латинская M или F)\n";
    ASSERT_TRUE(ui.add_user());
    actual = out.str();
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(ui.get_uid(), 0);
}
TEST_F(StreamUI_Test, Empty_or_failed_stream) {
    std::stringstream inp, out;
    MainController main;
    StreamUI ui{inp, out, &main};
    int i;
    char c;
    std::string expected;
    ASSERT_THROW(ui.inp(i), std::logic_error);
    ASSERT_THROW(ui.inp(c), std::logic_error);
    ASSERT_THROW(ui.inp(expected), std::logic_error);
    inp << "SMTH";
    inp.seekg(0);
    inp.setstate(std::ios_base::failbit);
    ASSERT_FALSE(ui.inp(i));
    inp.seekg(0);
    inp.setstate(std::ios_base::failbit);
    ASSERT_FALSE(ui.inp(c));
    inp.seekg(0);
    inp.setstate(std::ios_base::failbit);
    ASSERT_FALSE(ui.inp(expected));
}

TEST_F(StreamUI_Test, Print_services) {
    MainController main;
    std::stringstream out;
    StreamUI ui{std::cin, out, &main};
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    ui.print_services();
    std::string actual = out.str();
    std::string expected = "Dentist\n";
    ASSERT_EQ(actual, expected);
}

TEST_F(StreamUI_Test, Empty_services) {
    MainController main;
    std::stringstream out;
    StreamUI ui{std::cin, out, &main};
    ui.print_services();
    std::string actual = out.str();
    std::string expected = "Ошибка! Нет доступных услуг!\n";
    ASSERT_EQ(actual, expected);
}

TEST_F(StreamUI_Test, No_system_attached) {
    StreamUI ui{std::cin, std::cout};
    ASSERT_THROW(ui.add_user(), std::logic_error);
}
TEST_F(StreamUI_Test, Print_queue) {
    MainController main;
    std::stringstream out;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    serv.push_back("Therapist");
    StreamUI ui{std::cin, out, &main};
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 40, 'M');
    main.add_user(serv[0], "Semen", surname, 10, 100, 40, 'M');
    ui.set_uid(0);
    ui.print_queue();
    std::string actual, expected;
    expected = "Ваш идентификатор: 0\nIvan Ivanov. UID: 0\nSemen Ivanov. UID: 1\n";
    actual = out.str();
    ASSERT_EQ(actual, expected);
}
TEST_F(StreamUI_Test, Print_queue_nonexist_user) {
    MainController main;
    std::stringstream out;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    serv.push_back("Therapist");
    StreamUI ui{std::cin, out, &main};
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 40, 'M');
    ui.set_uid(1);
    ui.print_queue();
    std::string actual, expected;
    expected = "Ошибка! Пользователь не существует!\n";
    actual = out.str();
    ASSERT_EQ(actual, expected);
}

TEST_F(StreamUI_Test, Print_rooms) {
    MainController main;
    std::stringstream out;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    name = "Peter";
    serv.push_back("Therapist");
    main.add_room(name, surname, serv);
    StreamUI ui{std::cin, out, &main};
    std::string actual, expected;
    main.add_user(serv[1], name, surname, 10, 100, 10, 'M');
    ASSERT_NO_THROW(ui.print_rooms());
    expected = "0. Ivan Ivanov Dentist\nВ очереди 0\n1. Peter Ivanov Dentist Therapist\nВ очереди 1\n";
    actual = out.str();
    ASSERT_EQ(actual, expected);
}

TEST_F(StreamUI_Test, Remove_room) {
    MainController main;
    std::stringstream inp, out;
    std::string name, surname;
    std::vector<std::string> serv;
    std::string actual, expected;
    StreamUI ui{inp, out, &main};
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    name = "Peter";
    serv.push_back("Therapist");
    main.add_room(name, surname, serv);
    main.add_user(serv[1], name, surname, 10, 100, 10, 'M');
    expected = "Выберите удаляемого специалиста, введите его номер и нажмите enter: \n0. Ivan Ivanov Dentist\nВ очереди 0\n1. Peter Ivanov Dentist Therapist\nВ очереди 1\nСпециалист удалён!\n0. Ivan Ivanov Dentist\nВ очереди 0\nВыберите удаляемого специалиста, введите его номер и нажмите enter: \n0. Ivan Ivanov Dentist\nВ очереди 0\nОшибка! Нет комнаты с таким номером!\n";
    inp << 1 << std::endl << 1 << std::endl;
    ui.remove_room();
    ui.print_rooms();
    ui.remove_room();
    actual = out.str();
    ASSERT_EQ(actual, expected);
}

TEST_F(StreamUI_Test, Remove_rule) {
    MainController main;
    std::stringstream inp, out;
    std::string actual, expected;
    std::vector<std::string> serv;
    StreamUI ui{inp, out, &main};
    main.add_rule("ALL ", "height != 90");
    main.add_rule("weight < 80 ", "gender = M");
    expected = "Выберите удаляемое правило, введите его номер и нажмите enter: \n1. Prioritize ALL  over height != 90\n2. Prioritize weight < 80 over gender = M\nОшибка! Нет такого правила!\nВыберите удаляемое правило, введите его номер и нажмите enter: \n1. Prioritize ALL  over height != 90\n2. Prioritize weight < 80 over gender = M\nПравило удалено!\n1. Prioritize weight < 80 over gender = M\n";
    inp << 3 << std::endl << 1 << std::endl;
    ui.remove_rule();
    ui.remove_rule();
    ui.print_rules();
    actual = out.str();
    ASSERT_EQ(actual, expected);
}

TEST_F(StreamUI_Test, Print_rules) {
    MainController main;
    std::stringstream inp, out;
    StreamUI ui{inp, out, &main}; 
    std::string first, second;
    ui.print_rules();
    ASSERT_EQ(out.str(), "Нет правил определения приоритета!\n");
    out.str("");
    out.clear();
    first = "ALL ";
    second = "(gender = F)";
    main.add_rule(first, second);
    ui.print_rules();
    ASSERT_EQ(out.str(), "1. Prioritize ALL  over gender = F\n");
}
TEST_F(StreamUI_Test, Add_rule) {
    MainController main;
    std::stringstream inp, out;
    std::string expected, input;
    StreamUI ui{inp, out};
    ASSERT_THROW(ui.add_rule(), std::logic_error);
    ui.attach(&main);
    out.str("");
    expected = "Введите левое условие ";
    expected += "(корректное выражение на языке логических выражений) ";
    expected += "и нажмите enter: \n";
    expected += "Введите правое условие ";
    expected += "(корректное выражение на языке логических выражений) ";
    expected += "и нажмите enter: \n";
    input = "ALL \n gender = M\n";
    inp.str(input);
    ASSERT_NO_THROW(ui.add_rule());
    ASSERT_EQ(out.str(), expected);
}

TEST_F(StreamUI_Test, Login_logout) {
    MainController main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    main.add_user(serv[0], name, surname, 10, 100, 60, 'F');
    std::stringstream out;
    std::string actual, expected;
    StreamUI ui{std::cin, out, &main};
    ASSERT_FALSE(ui.login(2));
    ASSERT_TRUE(ui.login(1));
    ui.logout();
    ASSERT_FALSE(ui.login(1));
    ui.logout();
    expected = "Ошибка! Нет такого пользователя!\nОшибка! Нет такого пользователя!\nОшибка! Пользователь не существует!\n";
    actual = out.str();
    ASSERT_EQ(actual, expected);
}
TEST_F(StreamUI_Test, Save) {
    MainController main;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    main.add_room(name, surname, serv);
    std::stringstream out;
    StreamUI ui{std::cin, out, &main};
    ui.save();
    MainController loading;
    EXPECT_EQ(int(loading.get_services().size()), 1);
    EXPECT_EQ(int(loading.get_rooms().size()), 1);
    EXPECT_EQ(remove(MainController::rooms_file_name.c_str()), 0);
    EXPECT_EQ(remove(MainController::rules_file_name.c_str()), 0);
}
TEST_F(StreamUI_Test, Save_no_attached) {
    std::stringstream out;
    StreamUI ui{std::cin, out};
    ASSERT_THROW(ui.save(), std::logic_error);
}
