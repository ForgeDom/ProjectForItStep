#include "libs.h"

User::User(const string& username, const string& password)
    : username(username), password(password) {}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

bool User::verifyPassword(const string& inputPassword) const {
    return password == inputPassword;
}
