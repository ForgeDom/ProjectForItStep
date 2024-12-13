#include "Teacher.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Teacher::Teacher(const std::string& username, const std::string& password)
    : User(username, password) {}

Teacher::Teacher(std::ifstream& inFile) {
    std::getline(inFile, username);
    std::getline(inFile, password);
}

void Teacher::displayMenu() const {
    std::cout << "Teacher Menu: \n1. View Courses\n2. View Students in Course\n";
    std::cout << "3. Add Student to Course\n4. Remove Student from Course\n";
    std::cout << "5. Assign Grade to Student\n";
}

void Teacher::saveToFile(std::ofstream& outFile) const {
    outFile << username << '\n';
    outFile << password << '\n';
}

void Teacher::viewCourses(const std::vector<Course>& courses) const {
    std::cout << "Courses:\n";
    for (const auto& course : courses) {
        std::cout << "- " << course.getName() << '\n';
    }
}

void Teacher::viewStudentsInCourse(const std::vector<Course>& courses) const {
    std::string courseName;
    std::cout << "Enter course name: ";
    std::cin.ignore();
    std::getline(std::cin, courseName);

    for (const auto& course : courses) {
        if (course.getName() == courseName) {
            course.displayStudents();
            return;
        }
    }
    std::cout << "Course not found.\n";
}

void Teacher::addStudentToCourse(std::vector<Course>& courses) {
    std::string courseName, studentName;
    std::cout << "Enter course name: ";
    std::cin.ignore();
    std::getline(std::cin, courseName);
    std::cout << "Enter student name: ";
    std::getline(std::cin, studentName);

    for (auto& course : courses) {
        if (course.getName() == courseName) {
            course.addStudent(studentName);
            std::cout << "Student added successfully.\n";
            return;
        }
    }
    std::cout << "Course not found.\n";
}

void Teacher::removeStudentFromCourse(std::vector<Course>& courses) {
    std::string courseName, studentName;
    std::cout << "Enter course name: ";
    std::cin.ignore();
    std::getline(std::cin, courseName);
    std::cout << "Enter student name: ";
    std::getline(std::cin, studentName);

    for (auto& course : courses) {
        if (course.getName() == courseName) {
            course.removeStudent(studentName);
            std::cout << "Student removed successfully.\n";
            return;
        }
    }
    std::cout << "Course not found.\n";
}

void Teacher::assignGradeToStudent() {
    std::cout << "Feature not implemented yet.\n";
}

