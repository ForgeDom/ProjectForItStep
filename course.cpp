#include "libs.h"

Course::Course(const string& name) : name(name) {}
Course::Course(ifstream& inFile) {
    size_t nameSize;
    inFile >> nameSize;
    name.resize(nameSize);
    inFile.ignore();
    inFile.read(&name[0], nameSize);

    size_t studentCount;
    inFile >> studentCount;
    inFile.ignore();
    for (size_t i = 0; i < studentCount; ++i) {
        string studentName;
        getline(inFile, studentName);
        students.push_back(studentName);
    }
}


const string& Course::getName() const {
    return name;
}

const vector<string>& Course::getStudents() const {
    return students;
}

void Course::addStudent(const string& studentName) {
    students.push_back(studentName);
}

void Course::removeStudent(const string& studentName) {
    auto it = find(students.begin(), students.end(), studentName);
    if (it != students.end()) {
        students.erase(it);
    }
}

void Course::displayStudents() const {
    cout << "Students in course " << name << ":\n";
    for (const auto& student : students) {
        cout << "- " << student << '\n';
    }
}
