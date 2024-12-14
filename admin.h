#ifndef ADMIN_H
#define ADMIN_H
#include "libs.h"

class Admin : public User {
public:
    Admin(const string& username = "admin", const string& password = "admin");

    Admin(ifstream& inFile);

    vector<Course> courses;
    void saveToFile(ofstream& outFile) const;

    void displayMenu() const override;
    void viewStudents(const string& fileName) const;
    void viewTeachers(const string& fileName) const;
    void addTeacher(vector<User*>& users);
    void deleteTeacher(vector<User*>& users);
    void addStudent(vector<User*>& users);
    void deleteStudent(vector<User*>& users);
    void saveToFile(const string& filename, User* user) const;
    void addCourse(vector<Course>& courses);
    void deleteCourse(vector<Course>& courses);
};
#endif // !ADMIN_H