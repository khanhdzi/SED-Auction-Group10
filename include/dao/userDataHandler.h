// include/dao/UserDataHandler.h
#ifndef USER_DATA_HANDLER_H
#define USER_DATA_HANDLER_H

#include <vector>
#include <optional>
#include "../class/User.h"

class UserDataHandler {
private:
    static const std::string FILE_PATH;  // Path to the user data file

public:
    bool saveUser(const User& user);
    std::vector<User> getAllUsers();  // No const here
    std::optional<User> findUserByCredentials(const std::string& username, const std::string& password);
    std::optional<User> findUserById(const std::string& userId);  // No const here

    // New methods
    bool updateUser(const User& updatedUser);
    void displayUserDetails(const std::string& username);

    static const std::string& getFilePath() { return FILE_PATH; }
};

#endif // USER_DATA_HANDLER_H
