#ifndef USER_H
#define USER_H
#include "libs.h"

class User {
protected:
    string username;
    string password;

public:
    User(const string& username, const string& password);
    User() : username(""), password("") {}
    virtual void saveToFile(ofstream& outFile) const = 0;
    virtual ~User() = default;

    string getUsername() const;
    string getPassword() const;
    bool verifyPassword(const string& inputPassword) const;
    virtual void displayMenu() const = 0;
};

#endif // !USER_H