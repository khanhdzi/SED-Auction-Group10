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
    std::cout << "====================================\n";
    std::cout << "          User Registration          \n";
    std::cout << "====================================\n";
            
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

    std::string idType = "member";
    std::string idNumber = generateUserID();

    // Create a new user with default buyerRating and sellerRating as 3.0
    User newUser(username, password, fullName, phoneNumber, email, idType, idNumber);
    newUser.setCreditPoints(500);  // Initialize credit points
    newUser.setBuyerRating(3.0);   // Set default buyer rating
    newUser.setSellerRating(3.0);  // Set default seller rating

    if (userDAO.saveUser(newUser)) {
        std::cout << "User registered successfully.\n";
    } else {
        std::cout << "Failed to register user.\n";
    }
}

void Authenticator::Userlogin() {
    while (true) {
        std::cout << "====================================\n";
        std::cout << "            User Login          \n";
        std::cout << "====================================\n";
        // Get username input
        std::string username = InputValidator::validateString("Enter username (or -1 to exit): ");
        if (username == "-1") {
            std::cout << "Exiting login...\n";
            break;
        }

        // Get password input
        std::string password = InputValidator::validateString("Enter password (or -1 to exit): ");
        if (password == "-1") {
            std::cout << "Exiting login...\n";
            break;
        }

        // Validate password format
        if (!InputValidator::isValidPassword(password)) { // Corrected method name
            std::cout << "Invalid password format. Password must be at least 8 characters long and contain only letters and numbers.\n";
            continue;
        }

        // Authenticate user
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
