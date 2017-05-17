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
        do {
            msg("1. Новый пользователь");
            msg("2. Войти по идентификатору");
            msg("3. Войти как администратор");
            msg("4. Завершить работу системы");
            while (!inp(ans)) {
                err("Введите номер пункта!");
            }
            switch (ans) {
            case 1:
                std::cin.clear();
                clean();
                if (add_user()) {
                    clean();
                    user_menu();
                }
                break;
            case 2:
                msg("Введите индентификатор: ");
                while (!inp(ans)) {
                    err("Введите число!");
                }
                if (login(ans)) {
                    clean();
                    user_menu();
                }
                break;
            case 3:
                clean();
                admin_menu();
                break;
            case 4:
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
        msg("1. Проверить очередь");
        msg("2. Остаться в очереди и выйти в главное меню");
        msg("3. Покинуть очередь и выйти в главное меню");
        while (!inp(ans)) {
            err("Введите номер пункта!");
        }
        switch (ans) {
        case 1:
            clean();
            print_queue();
            break;
        case 2:
            clean();
            break;
        case 3:
            clean();
            logout();
            break;
        default:
            err("Нет такого пункта!");
        }
    } while (ans == 1);
}
void Client::admin_menu() {
    int ans;
    do {
        msg("1. Просмотреть список специалистов");
        msg("2. Добавить специалиста");
        msg("3. Удалить специалиста");
        msg("4. Просмотреть правила определения приоритетов");
        msg("5. Добавить правило");
        msg("6. Удалить правило");
        msg("7. Сохранить состояние системы");
        msg("8. Выйти в главное меню");
        while (!inp(ans)) {
            err("Введите номер пункта!");
        }
        switch (ans) {
        case 1:
            clean();
            print_rooms();
            break;
        case 2:
            clean();
            std::cin.clear();
            add_room();
            break;
        case 3:
            clean();
            std::cin.clear();
            remove_room();
            break;
        case 4:
            clean();
            print_rules();
            break;
        case 5:
            clean();
            std::cin.clear();
            add_rule();
            break;
        case 6:
            clean();
            std::cin.clear();
            remove_rule();
            break;
        case 7:
            clean();
            save();
            break;
        case 8:
            break;
        default:
            err("Нет такого пункта!");
        }
    } while (ans != 8);
}