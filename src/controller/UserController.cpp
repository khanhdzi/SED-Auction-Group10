#include "../../include/controller/UserController.h"
#include "../../include/utils/InputValidator.h"
#include <iostream>
#include <iomanip>
#include <algorithm>  // For std::remove_if
#include <fstream>    // For file I/O

void UserController::createUser() {
    // Validate username (check if it exists)
    std::string username = InputValidator::validateString("Enter username: ");
    if (isUsernameExist(username)) {
        std::cout << "Username already exists. Please choose a different one.\n";
        return;
    }

    // Validate password
    std::string password = InputValidator::validatePassword("Enter password: ");

    // Validate full name
    std::string fullName = InputValidator::validateString("Enter full name: ");

    // Validate phone number (check if it exists)
    std::string phoneNumber = InputValidator::validateString("Enter phone number: ");
    if (isPhoneNumberExist(phoneNumber)) {
        std::cout << "Phone number already exists. Please use a different one.\n";
        return;
    }

    // Validate email (check if it exists)
    std::string email = InputValidator::validateString("Enter email: ");
    if (isEmailExist(email)) {
        std::cout << "Email already exists. Please use a different one.\n";
        return;
    }

    // Validate user ID format (e.g., u-12345)
    std::string userID = InputValidator::validateUserID("Enter user ID: ");

    // Validate ID type (must be either "admin" or "member")
    std::string idType = InputValidator::validateString("Enter ID type (admin/member): ");
    if (idType != "admin" && idType != "member") {
        std::cout << "Invalid ID type. Please enter either 'admin' or 'member'.\n";
        return;
    }

    // Validate ID number
    std::string idNumber = InputValidator::validateString("Enter ID number: ");

    // Create new user
    User newUser(username, password, fullName, phoneNumber, email, idType, idNumber);

    // Save user to the database
    if (userDAO.saveUser(newUser)) {
        std::cout << "User created successfully.\n";
    } else {
        std::cout << "Failed to save user.\n";
    }
}


// Display all users
void UserController::displayAllUsers() {
    auto users = userDAO.getAllUsers();
    if (users.empty()) {
        std::cout << "No users found.\n";
        return;
    }

    std::cout << std::left << std::setw(15) << "Username" 
              << std::setw(20) << "Full Name"
              << std::setw(15) << "Phone"
              << std::setw(25) << "Email"
              << "\n" << std::string(75, '-') << "\n";

    for (const auto& user : users) {
        std::cout << std::left << std::setw(15) << user.getUsername()
                  << std::setw(20) << user.getFullName()
                  << std::setw(15) << user.getPhoneNumber()
                  << std::setw(25) << user.getEmail()
                  << "\n";
    }
}

// Display specific user info
void UserController::displayUserInfo(const std::string& username) {
    auto users = userDAO.getAllUsers();
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            std::cout << "Username: " << user.getUsername() << "\n"
                      << "Full Name: " << user.getFullName() << "\n"
                      << "Phone: " << user.getPhoneNumber() << "\n"
                      << "Email: " << user.getEmail() << "\n"
                      << "ID Type: " << user.getIdType() << "\n"
                      << "ID Number: " << user.getIdNumber() << "\n";
            return;
        }
    }
    std::cout << "User not found.\n";
}

// Delete a user by username
void UserController::deleteUser(const std::string& username) {
    auto users = userDAO.getAllUsers();
    auto it = std::remove_if(users.begin(), users.end(), [&](const User& user) {
        return user.getUsername() == username;
    });

    if (it != users.end()) {
        users.erase(it, users.end());

        // Rewrite the binary file with the remaining users
        std::ofstream file(UserDataHandler::getFilePath(), std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for rewriting.\n";
            return;
        }
        for (const auto& user : users) {
            user.serialize(file);
        }
        file.close();

        std::cout << "User deleted successfully.\n";
    } else {
        std::cout << "User not found.\n";
    }
}

// Edit the profile of a user
void UserController::editProfile(User& user) {
    std::cout << "Editing profile for user: " << user.getUsername() << "\n";

    std::string fullName = InputValidator::validateString("Enter new full name: ");
    std::string phoneNumber = InputValidator::validateString("Enter new phone number: ");
    std::string email = InputValidator::validateString("Enter new email: ");
    
    user.setFullName(fullName);
    user.setPhoneNumber(phoneNumber);
    user.setEmail(email);

    updateUser(user);
}

// Update a user's information
void UserController::updateUser(const User& user) {
    auto users = userDAO.getAllUsers();
    bool updated = false;

    for (auto& existingUser : users) {
        if (existingUser.getUsername() == user.getUsername()) {
            existingUser = user;
            updated = true;
            break;
        }
    }

    if (updated) {
        // Rewrite the binary file with the updated users
        std::ofstream file(UserDataHandler::getFilePath(), std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for rewriting.\n";
            return;
        }
        for (const auto& u : users) {
            u.serialize(file);
        }
        file.close();

        std::cout << "User updated successfully.\n";
    } else {
        std::cout << "User not found.\n";
    }
}
