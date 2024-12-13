#pragma once
#include <string>
#include <vector>

class Course {
private:
    std::string name;
    std::vector<std::string> students;

public:
    Course(const std::string& courseName);
    Course(std::ifstream& inFile);
    const std::string& getName() const;
    const std::vector<std::string>& getStudents() const;
    void addStudent(const std::string& studentName);
    void removeStudent(const std::string& studentName);
    void displayStudents() const;
};
