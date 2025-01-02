#include "../../include/class/Authenticator.h"
#include <iostream>

bool Authenticator::authenticate(const std::string& username, const std::string& password) {
    // Try to find user by credentials
    auto userOpt = userDAO.findUserByCredentials(username, password);
    if (userOpt) {
        loggedUser = new User(*userOpt);  // Allocate memory for loggedUser
        return true;
    }
    return false;
}

void Authenticator::logout() {
    if (loggedUser) {
        delete loggedUser;  // Free the allocated memory
        loggedUser = nullptr;
    }
}

bool Authenticator::isLoggedIn() {
    return loggedUser != nullptr;
}

User* Authenticator::getLoggedUser() {
    return loggedUser;
}
