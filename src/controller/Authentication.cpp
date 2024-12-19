// src/controller/Authentication.cpp
#include "../../include/controller/Authentication.h"
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <filesystem>

const std::string Authentication::USER_DATA_FILE = "data/users.dat";

Authentication::Authentication() {
    // Create data directory if it doesn't exist
    std::filesystem::path dataPath("data");
    if (!std::filesystem::exists(dataPath)) {
        std::filesystem::create_directory(dataPath);
    }
    loadUsers();
}

std::optional<User> Authentication::login(const std::string& username, const std::string& password) {
    // Reload users to ensure we have the latest data
    loadUsers();
    
    // Find user with matching username and validate password
    auto it = std::find_if(users.begin(), users.end(),
        [&username](const User& user) {
            return user.getUsername() == username;
        });

    if (it != users.end() && it->validatePassword(password) && it->getIsActive()) {
        return *it;
    }
    
    return std::nullopt;
}

bool Authentication::registerUser(const std::string& username, const std::string& password,
                                const std::string& fullName, const std::string& phoneNumber,
                                const std::string& email, const std::string& idType,
                                const std::string& idNumber) {
    // Reload users to ensure we have the latest data
    loadUsers();

    // Validate username availability
    if (!isUsernameAvailable(username)) {
        return false;
    }

    // Validate password format
    if (!isValidPassword(password)) {
        return false;
    }

    try {
        // Create new user and add to vector
        User newUser(username, password, fullName, phoneNumber, email, idType, idNumber);
        users.push_back(newUser);
        
        // Save updated user list
        saveUsers();
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool Authentication::isUsernameAvailable(const std::string& username) {
    return std::none_of(users.begin(), users.end(),
        [&username](const User& user) {
            return user.getUsername() == username;
        });
}

bool Authentication::validateLoginCredentials(const std::string& username, const std::string& password) {
    auto it = std::find_if(users.begin(), users.end(),
        [&username](const User& user) {
            return user.getUsername() == username;
        });

    return (it != users.end() && it->validatePassword(password));
}

void Authentication::loadUsers() {
    users = UserDataHandler::loadUsersFromFile(USER_DATA_FILE);
}

void Authentication::saveUsers() {
    UserDataHandler::saveUsersToFile(users, USER_DATA_FILE);
}

bool Authentication::isValidPassword(const std::string& password) {
    // Check minimum length requirement
    if (password.length() < 8) {
        return false;
    }

    // Check that password only contains letters and numbers (no special characters)
    for (char c : password) {
        if (!std::isalnum(c)) {
            return false;
        }
    }

    return true;
}