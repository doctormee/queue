#include "StreamUI.h"
#include "MainController.h"
#include <iostream>

int main() {
    MainController data;
    StreamUI ui{std::cin, std::cout, &data};
    return 0;
}