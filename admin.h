#pragma once
#include "User.h"
#include "Teacher.h"
#include "Student.h"
#include "course.h"
#include <fstream>
#include <iostream>

class Admin : public User {
public:
    Admin(const std::string& username = "admin", const std::string& password = "admin");

    Admin(std::ifstream& inFile);

    void saveToFile(std::ofstream& outFile) const;

    void displayMenu() const override;
    void viewStudents(const std::vector<User*>& users) const;
    void viewTeachers(const std::vector<User*>& users) const;
    void addTeacher(std::vector<User*>& users);
    void deleteTeacher(std::vector<User*>& users);
    void addStudent(std::vector<User*>& users);
    void deleteStudent(std::vector<User*>& users);
    void saveToFile(const std::string& filename, User* user) const;
    void addCourse(std::vector<Course>& courses);
    void deleteCourse(std::vector<Course>& courses);
};
