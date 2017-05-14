#include "StreamUI.h"
#include "System.h"
#include "gtest/gtest.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

TEST(StreamUI_Test, Message) {
    std::stringstream inp, out;
    StreamUI ui(inp, out);
    std::string expected = "Hello, World!";
    ui.msg(expected);
    std::string actual;
    std::getline(out, actual);
    ASSERT_EQ(actual, expected);
}
TEST(StreamUI_Test, Error) {
    std::stringstream inp, out;
    StreamUI ui(inp, out);
    std::string expected = "All gone wrong!";
    ui.err(expected);
    std::string actual;
    std::getline(out, actual);
    expected = "Ошибка! All gone wrong!";
    ASSERT_EQ(actual, expected);
}

TEST(StreamUI_Test, Add_room) {
    std::stringstream inp, out;
    std::string actual, expected, empty;
    empty.clear();
    StreamUI ui(inp, out);
    System main;
    ui.attach(&main);
    inp << empty << std::endl << "John" << std::endl << empty << std::endl << "Appleseed" << std::endl << "Dental" << std::endl << "Therapist" << std::endl << "end" << std::endl;
    ui.add_room();
    expected = "Введите имя специалиста: \nОшибка! Некорректное имя!\nВведите имя специалиста: \nВведите фамилию специалиста: \nОшибка! Некорректная фамилия!\nВведите фамилию специалиста: \nВведите услуги, оказываемые специалистом, по одной услуге на строку. В конце ввода введите строку end\n";
    actual = out.str();
    ASSERT_EQ(actual, expected);
}
TEST(StreamUI_Test, Add_user) {
    std::stringstream inp, out;
    StreamUI ui(inp, out);
    System main;
    std::string name, surname, actual, expected, empty;
    empty.clear();
    std::vector<std::string> serv;
    name = "Иван";
    surname = "Иванов";
    serv.push_back("Дантист");
    main.add_room(name, surname, serv);
    ui.attach(&main);
    ui.set_uid(1);
    inp << 1 << std::endl << "Дантист" << std::endl << empty << std::endl << "Иван" << std::endl << empty << std::endl << "Иванов" << std::endl << "as" << std::endl << 1 << std::endl << "as" << std::endl << 2 << std::endl << "as" << std::endl << 3 << std::endl << 10 << std::endl << 'a' << std::endl << 'M'<< std::endl;
    expected = "Выберите услугу (или введите exit для выхода)\nДантист\nОшибка! Нет такой услуги!\nВыберите услугу (или введите exit для выхода)\nДантист\nВведите имя\nОшибка! Некорректное имя!\nВведите имя\nВведите фамилию\nОшибка! Некорректная фамилия!\nВведите фамилию\nВведите свой возраст (в годах)\nОшибка! Некорректный возраст!\nВведите свой возраст (в годах)\nВведите свой рост (в см)\nОшибка! Некорректный рост!\nВведите свой рост (в см)\nВведите свой вес (в кг)\nОшибка! Некорректный вес!\nВведите свой вес (в кг)\nВведите пол (латинская M или F)\nОшибка! Некорректный пол!\nВведите пол (латинская M или F)\nОшибка! Некорректный пол!\nВведите пол (латинская M или F)\nОшибка! Некорректный пол!\nВведите пол (латинская M или F)\n";
    inp.flush();
    ui.add_user();
    actual = out.str();
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(ui.get_uid(), 0);
}
TEST(StreamUI_Test, Empty_or_failed_stream) {
    std::stringstream inp, out;
    System main;
    StreamUI ui(inp, out, &main);
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

TEST(StreamUI_Test, Print_services) {
    System main;
    std::stringstream out;
    StreamUI ui(std::cin, out, &main);
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

TEST(StreamUI_Test, Empty_services) {
    System main;
    std::stringstream out;
    StreamUI ui(std::cin, out, &main);
    ui.print_services();
    std::string actual = out.str();
    std::string expected = "Ошибка! Нет доступных услуг!\n";
    ASSERT_EQ(actual, expected);
}

TEST(StreamUI_Test, No_system_attached) {
    StreamUI ui(std::cin, std::cout);
    ASSERT_THROW(ui.add_user(), std::logic_error);
}
TEST(StreamUI_Test, Print_queue) {
    System main;
    std::stringstream out;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    serv.push_back("Therapist");
    StreamUI ui(std::cin, out, &main);
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 40, 'M');
    main.add_user(serv[0], "Semen", surname, 10, 100, 40, 'M');
    ui.set_uid(0);
    ui.print_queue();
    std::string actual, expected;
    expected = "Ваш идентификатор: 0\nIvan Ivanov. Идентификатор: 0\nSemen Ivanov. Идентификатор: 1\nВаш номер в очереди: 1\n";
    actual = out.str();
    ASSERT_EQ(actual, expected);
}
TEST(StreamUI_Test, Print_queue_nonexist_user) {
    System main;
    std::stringstream out;
    std::string name, surname;
    std::vector<std::string> serv;
    name = "Ivan";
    surname = "Ivanov";
    serv.push_back("Dentist");
    serv.push_back("Therapist");
    StreamUI ui(std::cin, out, &main);
    main.add_room(name, surname, serv);
    main.add_user(serv[0], name, surname, 10, 100, 40, 'M');
    ui.set_uid(1);
    ui.print_queue();
    std::string actual, expected;
    expected = "Ошибка! Пользователь не существует!\n";
    actual = out.str();
    ASSERT_EQ(actual, expected);
}

TEST(StreamUI_Test, Print_rooms) {
    System main;
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
    StreamUI ui(std::cin, out, &main);
    std::string actual, expected;
    ASSERT_NO_THROW(ui.print_rooms());
    expected = "Ivan Ivanov. Услуги: Dentist \nPeter Ivanov. Услуги: Dentist Therapist \n";
    actual = out.str();
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

