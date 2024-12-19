#include "../../include/controller/UserService.h"
#include <algorithm>
#include <stdexcept>

UserService::UserService() {
    reloadUsers();
}

void UserService::reloadUsers() {
    users = UserDataHandler::loadUsersFromFile(DATA_FILE);
}

void UserService::saveUsers() {
    UserDataHandler::saveUsersToFile(users, DATA_FILE);
}

std::vector<User> UserService::getAllUsers() const {
    return users;
}

bool UserService::addUser(const User& user) {
    if (std::any_of(users.begin(), users.end(),
        [&user](const User& existingUser) {
            return existingUser.getUsername() == user.getUsername();
        })) {
        return false; // Username already exists
    }

    users.push_back(user);
    saveUsers();
    return true;
}

bool UserService::updateUser(const std::string& username, const User& updatedUser) {
    auto it = std::find_if(users.begin(), users.end(),
        [&username](const User& user) {
            return user.getUsername() == username;
        });

    if (it != users.end()) {
        *it = updatedUser;
        saveUsers();
        return true;
    }

    return false; // User not found
}

bool UserService::deleteUser(const std::string& username) {
    auto it = std::remove_if(users.begin(), users.end(),
        [&username](const User& user) {
            return user.getUsername() == username;
        });

    if (it != users.end()) {
        users.erase(it, users.end());
        saveUsers();
        return true;
    }

    return false; // User not found
}

std::optional<User> UserService::findUserByUsername(const std::string& username) const {
    auto it = std::find_if(users.begin(), users.end(),
        [&username](const User& user) {
            return user.getUsername() == username;
        });

    if (it != users.end()) {
        return *it;
    }

    return std::nullopt; // User not found
}
