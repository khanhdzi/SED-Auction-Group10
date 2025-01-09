// include/controller/UserController.h
#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "../class/user.h"
#include "../class/Authenticator.h"
#include "../dao/userDataHandler.h"



class UserController {
private:
    UserDataHandler userDAO;
public:
    void createUser();
   
    void displayAllUsers();
    void displayUserInfo(const std::string& username);
    void deleteUser(const std::string& username);
    void editProfile(User& user);
    void updateUser(const User& user);
};

#endif