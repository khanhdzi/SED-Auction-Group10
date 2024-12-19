#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "../class/User.h"
#include "../dao/UserDataHandler.h"
#include <vector>
#include <optional>

class UserService {
private:
    std::vector<User> users;
    const std::string DATA_FILE = "data/users.dat";

    // Reloads the user list from the data file
    void reloadUsers();

    // Saves the user list to the data file
    void saveUsers();

public:
    UserService();

    // Get all users
    std::vector<User> getAllUsers() const;

    // Add a new user
    bool addUser(const User& user);

    // Update user details
    bool updateUser(const std::string& username, const User& updatedUser);

    // Delete a user by username
    bool deleteUser(const std::string& username);

    // Find a user by username
    std::optional<User> findUserByUsername(const std::string& username) const;
};

#endif
