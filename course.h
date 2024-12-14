#ifndef COURSE_H
#define COURSE_H
#include "libs.h"

class Course {
private:
    string name;
    vector<string> students;
public:
    Course(const string& name);
    Course(ifstream& inFile);
    const string& getName() const;
    const vector<string>& getStudents() const;
    void addStudent(const string& studentName);
    void removeStudent(const string& studentName);
    void displayStudents() const;
};

#endif // !COURSE_H