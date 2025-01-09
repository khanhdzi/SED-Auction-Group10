// include/class/Authenticator.h
#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include "../class/user.h"
#include "../dao/userDataHandler.h"
#include <optional>

class Authenticator {
private:
    static inline User* loggedUser = nullptr;
    static inline UserDataHandler userDAO;

    // Check if the username already exists
    bool isUsernameExist(const std::string& username);

    // Check if the phone number already exists
    bool isPhoneNumberExist(const std::string& phoneNumber);

    // Check if the email already exists
    bool isEmailExist(const std::string& email);

    // Generate user ID (auto-incrementing, format: u-XXXXX)
    std::string generateUserID();


public:
    static bool authenticate(const std::string& username, const std::string& password);
    static void logout();
    static bool isLoggedIn();
    static User* getLoggedUser();
    void registerUser();
    void Userlogin();
};

#endif