#pragma once
#include <string>
#include <fstream>

class User {
protected:
    std::string username;
    std::string password;

public:
    User(const std::string& username, const std::string& password);
    User() : username(""), password("") {}
    virtual void saveToFile(std::ofstream& outFile) const = 0;
    virtual ~User() = default;

    std::string getUsername() const;
    std::string getPassword() const;
    bool verifyPassword(const std::string& inputPassword) const;
    virtual void displayMenu() const = 0;
};
