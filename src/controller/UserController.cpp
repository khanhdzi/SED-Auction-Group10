#include "../../include/controller/UserController.h"
#include "../../include/utils/InputValidator.h"
#include "../../include/class/Authenticator.h"
#include <iostream>
#include <iomanip>
#include <algorithm>  // For std::remove_if
#include <fstream>    // For file I/O


// Create a new user
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
            std::cout << "User Information:\n";
            std::cout << "-----------------\n";
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
    std::cout << "Press Enter to skip updating a field.\n";

    // Prompt for a new full name
    std::string fullName;
    std::cout << "Enter new full name (current: " << user.getFullName() << "): ";
    std::getline(std::cin >> std::ws, fullName); // Clear whitespace before getline
    if (!fullName.empty()) {
        user.setFullName(fullName);
    }

    // Prompt for a new phone number
    std::string phoneNumber;
    std::cout << "Enter new phone number (current: " << user.getPhoneNumber() << "): ";
    std::getline(std::cin, phoneNumber); // No need for std::ws here as cin.ignore is handled
    if (!phoneNumber.empty()) {
        if (InputValidator::isValidPhoneNumber(phoneNumber)) {
            user.setPhoneNumber(phoneNumber);
        } else {
            std::cout << "Invalid phone number format. Skipping update.\n";
        }
    }

    // Prompt for a new email
    std::string email;
    std::cout << "Enter new email (current: " << user.getEmail() << "): ";
    std::getline(std::cin, email); // No need for std::ws here as cin.ignore is handled
    if (!email.empty()) {
        if (InputValidator::isValidEmail(email)) {
            user.setEmail(email);
        } else {
            std::cout << "Invalid email format. Skipping update.\n";
        }
    }

    // Save updated information
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

// Function to check if a username exists
bool UserController::isUsernameExist(const std::string& username) {
    auto users = userDAO.getAllUsers();
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            return true;  // Username exists
        }
    }
    return false;  // Username does not exist
}

// Function to check if a phone number exists
bool UserController::isPhoneNumberExist(const std::string& phoneNumber) {
    auto users = userDAO.getAllUsers();
    for (const auto& user : users) {
        if (user.getPhoneNumber() == phoneNumber) {
            return true;  // Phone number exists
        }
    }
    return false;  // Phone number does not exist
}

// Function to check if an email exists
bool UserController::isEmailExist(const std::string& email) {
    auto users = userDAO.getAllUsers();
    for (const auto& user : users) {
        if (user.getEmail() == email) {
            return true;  // Email exists
        }
    }
    return false;  // Email does not exist
}

// Function to get all user into vector
std::vector<User> UserController::getAllUsers() {
    return userDAO.getAllUsers();
}
