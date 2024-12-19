#include "../../include/ui/LoginScreen.h"
#include "../../include/utils/InputValidator.h"
#include "../../include/controller/Authentication.h"
#include <iostream>

LoginScreen::LoginScreen() {}

void LoginScreen::display() {
    displayHeader();
    displayLoginForm();
}

void LoginScreen::displayHeader() {
    std::cout << "\n=================================\n";
    std::cout << "           LOGIN SCREEN          \n";
    std::cout << "=================================\n";
}

void LoginScreen::displayLoginForm() {
    std::string username = InputValidator::validateString("Enter username: ");
    std::string password = InputValidator::validateString("Enter password: ");

    Authentication auth;
    auto user = auth.login(username, password);

    if (user.has_value()) {
        showLoginSuccess(user.value());
    } else {
        showLoginError();
    }
}

void LoginScreen::showLoginSuccess(const User& user) {
    std::cout << "\nLogin successful! Welcome, " << user.getFullName() << "!\n";
}

void LoginScreen::showLoginError() {
    std::cout << "\nError: Invalid username or password. Please try again.\n";
}

void LoginScreen::showRegisterSuccess() {
    std::cout << "\nRegistration successful! Please login with your new credentials.\n";
}

void LoginScreen::showRegisterError(const std::string& message) {
    std::cout << "\nRegistration failed: " << message << "\n";
}