#ifndef STUDENT_H
#define STUDENT_H
#include "libs.h"
class Student : public User {
public:
    Student(const string& username, const string& password);
    Student(ifstream& inFile);
    void saveToFile(ofstream& outFile) const;
    void displayMenu() const override;
};

#endif // !STUDENT_H