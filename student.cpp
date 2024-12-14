#include "libs.h"

Student::Student(const string& username, const string& password)
    : User(username, password) {}

Student::Student(ifstream& inFile) {
    getline(inFile, username);
    getline(inFile, password);
}

void Student::saveToFile(ofstream& outFile) const {
    outFile << username << '\n';
    outFile << password << '\n';
}

void Student::displayMenu() const {
    cout << "Student Menu: \n1. View Courses\n2. View Grades\n";
}
