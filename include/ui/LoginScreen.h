#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include "../class/User.h"
#include <string>

class LoginScreen {
public:
    LoginScreen();
    void display();
    void showLoginSuccess(const User& user);
    void showLoginError();
    void showRegisterSuccess();
    void showRegisterError(const std::string& message);

private:
    void displayHeader();
    void displayLoginForm();
};

#endif