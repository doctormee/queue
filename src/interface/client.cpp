#include "MainController.h"
#include "StreamUI.h"
#include "Client.h"
#include <iostream>
#include <stdexcept>
Client::Client()
    : StreamUI{std::cin, std::cout, &data}
{
}
const int Client::BREAK_LINES = 100;
void Client::clean() {
    for (int i = 0; i  <= BREAK_LINES; ++i) {
        msg("\n");
    }
}
void Client::login_menu() {
    int ans;
    try {
        clean();
        do {
            msg("ГЛАВНОЕ МЕНЮ (введите номер пункта)");
            msg("1. Новый пользователь");
            msg("2. Войти по идентификатору");
            msg("3. Войти как администратор");
            msg("4. Завершить работу системы");
            while (!inp(ans)) {
                err("Введите номер пункта!");
            }
            switch (ans) {
            case 1: //Новый пользователь
                std::cin.clear();
                clean();
                if (add_user()) {
                    clean();
                    user_menu();
                }
                break;
            case 2: //Войти по идентификатору
                clean();
                msg("Введите индентификатор: ");
                while (!inp(ans)) {
                    clean();
                    err("Введите число!");
                }
                if (login(ans)) {
                    clean();
                    user_menu();
                }
                break;
            case 3: //Войти как администратор
                clean();
                admin_menu();
                break;
            case 4: //Завершить работу системы
                clean();
                break;
            default:
                err("Нет такого пункта!");
            }
        } while (ans != 4);
    } catch (std::exception &ex) {
        err(ex.what());
    }
    save();
}
void Client::user_menu() {
    int ans;
    do {
        msg("МЕНЮ ПОЛЬЗОВАТЕЛЯ (введите номер пункта)");
        msg("1. Проверить очередь");
        msg("2. Остаться в очереди и выйти в главное меню");
        msg("3. Покинуть очередь и выйти в главное меню");
        while (!inp(ans)) {
            err("Введите номер пункта!");
        }
        switch (ans) {
        case 1: //Проверить очередь
            clean();
            print_queue();
            break;
        case 2: //Остаться в очереди и выйти в главное меню
            clean();
            break;
        case 3: //Покинуть очередь и выйти в главное меню
            clean();
            logout();
            break;
        default:
            err("Нет такого пункта!");
        }
    } while ((ans != 2) && (ans != 3));
}
void Client::admin_menu() {
    int ans;
    clean();
    do {
        msg("МЕНЮ АДМИНИСТРАТОРА (введите номер пункта)");
        msg("1. Просмотреть список услуг");
        msg("2. Просмотреть список специалистов");
        msg("3. Добавить специалиста");
        msg("4. Удалить специалиста");
        msg("5. Просмотреть правила определения приоритетов");
        msg("6. Добавить правило");
        msg("7. Удалить правило");
        msg("8. Сохранить состояние системы");
        msg("9. Выйти в главное меню");
        while (!inp(ans)) {
            err("Введите номер пункта!");
        }
        switch (ans) {
        case 1: //Просмотреть список услуг
            clean();
            print_services();
            break;
        case 2: //Просмотреть список специалистов
            clean();
            print_rooms();
            break;
        case 3: //Добавить специалиста
            clean();
            std::cin.clear();
            add_room();
            break;
        case 4: //Удалить специалиста
            clean();
            std::cin.clear();
            remove_room();
            break;
        case 5: //Просмотреть правила определения приоритетов
            clean();
            print_rules();
            break;
        case 6: //Добавить правило
            clean();
            std::cin.clear();
            add_rule();
            break;
        case 7: //Удалить правило
            clean();
            std::cin.clear();
            remove_rule();
            break;
        case 8: //Сохранить состояние системы
            clean();
            save();
            break;
        case 9: //Выйти в главное меню
            clean();
            break;
        default:
            err("Нет такого пункта!");
        }
    } while (ans != 9);
}