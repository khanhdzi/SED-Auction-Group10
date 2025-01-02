// include/class/Authenticator.h
#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include "user.h"
#include "../dao/userDataHandler.h"
#include <optional>

class Authenticator {
private:
    static inline User* loggedUser = nullptr;
    static inline UserDataHandler userDAO;

public:
    static bool authenticate(const std::string& username, const std::string& password);
    static void logout();
    static bool isLoggedIn();
    static User* getLoggedUser();
};

#endif