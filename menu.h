#ifndef MENU_H
#define MENU_H
#include "libs.h"

class Menu {
private:
    vector<User*> users;
    vector<Course> courses;

    void saveUsersToFile() const;
    void loadUsersFromFile();
    void adminMenu(Admin* admin);
    void teacherMenu(Teacher* teacher);
    void studentMenu(Student* student);
    void registerStudent();

public:
    Menu();
    ~Menu();
    void displayMainMenu();
};

#endif // !MENU_H