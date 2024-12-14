#include "libs.h"

int main() {
    try {
        Menu menu;
        menu.displayMainMenu();
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
