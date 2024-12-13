#pragma once
#include "User.h"

class Student : public User {
public:
    Student(const std::string& username, const std::string& password);
    Student(std::ifstream& inFile);
    void saveToFile(std::ofstream& outFile) const;
    void displayMenu() const override;

};
