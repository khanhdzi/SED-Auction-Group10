#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "../class/user.h"
#include "../class/Authenticator.h"
#include "../dao/userDataHandler.h"

class UserController {
private:
    UserDataHandler userDAO;  // This manages the user data
public:
    void createUser();
    void displayAllUsers();
    void displayUserInfo(const std::string& username);
    void deleteUser(const std::string& username);
    void editProfile(User& user);
    void updateUser(const User& user);

    // Add these functions to check if the username, phone number, or email exist
    bool isUsernameExist(const std::string& username);
    bool isPhoneNumberExist(const std::string& phoneNumber);
    bool isEmailExist(const std::string& email);
};

#endif
