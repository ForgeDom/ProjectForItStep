#pragma once
#include "User.h"
#include "Course.h"

class Teacher : public User {
public:
    Teacher(const std::string& username, const std::string& password);
    Teacher(std::ifstream& inFile);
    void displayMenu() const override;

    void viewCourses(const std::vector<Course>& courses) const;
    void viewStudentsInCourse(const std::vector<Course>& courses) const;
    void addStudentToCourse(std::vector<Course>& courses);
    void removeStudentFromCourse(std::vector<Course>& courses);
    void assignGradeToStudent();

    void saveToFile(std::ofstream& outFile) const;


};
