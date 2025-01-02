#include "../../include/dao/UserDataHandler.h"
#include <fstream>
#include <iostream>

const std::string UserDataHandler::FILE_PATH = "data/users.dat";

// Save a user to the binary file
bool UserDataHandler::saveUser(const User& user) {
    std::ofstream file(FILE_PATH, std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving user.\n";
        return false;
    }
    user.serialize(file);
    file.close();
    return true;
}

// Get all users from the binary file
std::vector<User> UserDataHandler::getAllUsers() {
    std::vector<User> users;
    std::ifstream file(FILE_PATH, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading users.\n";
        return users;
    }

    // Read users from the file until the end
    while (file.peek() != EOF) {
        User user;
        user.deserialize(file);
        users.push_back(user);
    }

    file.close();
    return users;
}

// Find user by username and password
std::optional<User> UserDataHandler::findUserByCredentials(const std::string& username, const std::string& password) {
    std::vector<User> users = getAllUsers();
    for (const auto& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return user; // Return the matching user
        }
    }
    return std::nullopt; // No user found with the provided credentials
}
