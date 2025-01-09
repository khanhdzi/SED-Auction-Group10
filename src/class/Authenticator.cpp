#include "../../include/class/Authenticator.h"
#include "../../include/utils/InputValidator.h"
#include <iostream>
#include <sstream>  // For stringstream
#include <iomanip>  // For setw and setfill

bool Authenticator::authenticate(const std::string& username, const std::string& password) {
    auto userOpt = userDAO.findUserByCredentials(username, password);
    if (userOpt) {
        loggedUser = new User(*userOpt);
        return true;
    }
    return false;
}

void Authenticator::logout() {
    if (loggedUser) {
        delete loggedUser;
        loggedUser = nullptr;
    }
}

bool Authenticator::isLoggedIn() {
    return loggedUser != nullptr;
}

User* Authenticator::getLoggedUser() {
    return loggedUser;
}

void Authenticator::registerUser() {
    std::string username = InputValidator::validateString("Enter username: ");
    if (isUsernameExist(username)) {
        std::cout << "Username already exists. Please choose a different one.\n";
        return;
    }

    std::string password = InputValidator::validatePassword("Enter password: ");
    std::string fullName = InputValidator::validateString("Enter full name: ");
    std::string phoneNumber = InputValidator::validateString("Enter phone number: ");
    if (isPhoneNumberExist(phoneNumber)) {
        std::cout << "Phone number already exists. Please use a different one.\n";
        return;
    }

    std::string email = InputValidator::validateString("Enter email: ");
    if (isEmailExist(email)) {
        std::cout << "Email already exists. Please use a different one.\n";
        return;
    }

    std::string userID = generateUserID();
    std::string idType = "member";
    std::string idNumber = InputValidator::validateString("Enter ID number: ");
    User newUser(username, password, fullName, phoneNumber, email, idType, idNumber);

    if (userDAO.saveUser(newUser)) {
        std::cout << "User registered successfully.\n";
    } else {
        std::cout << "Failed to register user.\n";
    }
}

void Authenticator::Userlogin() {
    while (true) {
        std::string username = InputValidator::validateString("Enter username (or -1 to exit): ");
        std::string password = InputValidator::validatePassword("Enter password (or -1 to exit): ");

        if (username == "-1" && password == "-1") {
            std::cout << "Exiting login...\n";
            break;
        }

        if (this->authenticate(username, password)) {
            std::cout << "Login successful.\n";
            break;
        } else {
            std::cout << "Invalid username or password. Please try again.\n";
        }
    }
}

std::string Authenticator::generateUserID() {
    std::vector<User> users = userDAO.getAllUsers();
    int newUserId = users.size() + 1;
    std::stringstream ss;
    ss << "u-" << std::setw(5) << std::setfill('0') << newUserId;
    return ss.str();
}

bool Authenticator::isUsernameExist(const std::string& username) {
    std::vector<User> users = userDAO.getAllUsers();
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            return true;
        }
    }
    return false;
}

bool Authenticator::isPhoneNumberExist(const std::string& phoneNumber) {
    std::vector<User> users = userDAO.getAllUsers();
    for (const auto& user : users) {
        if (user.getPhoneNumber() == phoneNumber) {
            return true;
        }
    }
    return false;
}

bool Authenticator::isEmailExist(const std::string& email) {
    std::vector<User> users = userDAO.getAllUsers();
    for (const auto& user : users) {
        if (user.getEmail() == email) {
            return true;
        }
    }
    return false;
}
