#include "Student.h"
#include <iostream>

Student::Student(const std::string& username, const std::string& password)
    : User(username, password) {}

Student::Student(std::ifstream& inFile) {
    std::getline(inFile, username);
    std::getline(inFile, password);
}

void Student::saveToFile(std::ofstream& outFile) const {
    outFile << username << '\n';
    outFile << password << '\n';
}

void Student::displayMenu() const {
    std::cout << "Student Menu: \n1. View Courses\n2. View Grades\n";
}
