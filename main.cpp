#include <iostream>
#include "menu.h"

int main() {
    try {
        Menu menu;
        menu.displayMainMenu();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
