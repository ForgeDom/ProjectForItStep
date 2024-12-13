#include "User.h"

User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

bool User::verifyPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}
