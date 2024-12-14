#ifndef TEACHER_H
#define TEACHER_H
#include "libs.h"

class Teacher : public User {
public:
    Teacher(const string& username, const string& password);
    Teacher(ifstream& inFile);
    void displayMenu() const override;

    void saveToFile(ofstream& outFile) const;
    void viewCourses(const string& fileName) const;
    void viewStudentsInCourse(const string& fileName) const;
    void addStudentToCourse(const string& fileName);
    void removeStudentFromCourse(const string& fileName);
    void assignGradeToStudent(const string& fileName);
};
#endif // !TEACHER_H