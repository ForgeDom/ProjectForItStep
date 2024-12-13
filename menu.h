#pragma once
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
#include "Course.h"
#include <vector>

class Menu {
private:
    std::vector<User*> users;
    std::vector<Course> courses;

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
