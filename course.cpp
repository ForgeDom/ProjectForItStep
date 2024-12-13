#include "Course.h"
#include <iostream>
#include <fstream>

Course::Course(const std::string& courseName) : name(courseName) {}
Course::Course(std::ifstream& inFile) {
    size_t nameSize;
    inFile >> nameSize;
    name.resize(nameSize);
    inFile.ignore();
    inFile.read(&name[0], nameSize);

    size_t studentCount;
    inFile >> studentCount;
    inFile.ignore();
    for (size_t i = 0; i < studentCount; ++i) {
        std::string studentName;
        std::getline(inFile, studentName);
        students.push_back(studentName);
    }
}


const std::string& Course::getName() const {
    return name;
}

const std::vector<std::string>& Course::getStudents() const {
    return students;
}

void Course::addStudent(const std::string& studentName) {
    students.push_back(studentName);
}

void Course::removeStudent(const std::string& studentName) {
    auto it = std::find(students.begin(), students.end(), studentName);
    if (it != students.end()) {
        students.erase(it);
    }
}

void Course::displayStudents() const {
    std::cout << "Students in course " << name << ":\n";
    for (const auto& student : students) {
        std::cout << "- " << student << '\n';
    }
}
