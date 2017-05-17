#pragma once
#include "StreamUI.h"
#include "MainController.h"

class Client: protected StreamUI {
    MainController data;
    void user_menu();
    void admin_menu();
    void clean();
    static const int BREAK_LINES;
public:
    Client();
    void login_menu();
};