// include/controller/UserController.h
#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "../class/user.h"
#include "../dao/userDataHandler.h"


class UserController {
private:
    UserDataHandler userDAO;
    // Check if the username already exists
    bool isUsernameExist(const std::string& username);

    // Check if the phone number already exists
    bool isPhoneNumberExist(const std::string& phoneNumber);

    // Check if the email already exists
    bool isEmailExist(const std::string& email);

    // Generate user ID (auto-incrementing, format: u-XXXXX)
    std::string generateUserID();
public:
    void createUser();
    void registerUser();
    void displayAllUsers();
    void displayUserInfo(const std::string& username);
    void deleteUser(const std::string& username);
    void editProfile(User& user);
    void updateUser(const User& user);
};

#endif