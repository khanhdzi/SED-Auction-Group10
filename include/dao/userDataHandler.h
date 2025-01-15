// include/dao/UserDataHandler.h
#ifndef USER_DATA_HANDLER_H
#define USER_DATA_HANDLER_H

#include <vector>
#include <optional>
#include "../class/user.h"

class UserDataHandler {
private:
    static const std::string FILE_PATH;  // Declare as static

public:
    bool saveUser(const User& user);
    std::vector<User> getAllUsers();
    std::optional<User> findUserByCredentials(const std::string& username, const std::string& password);
     // New methods
    bool updateUser(const User& updatedUser); // Updates a user in the users.dat file
    void displayUserDetails(const std::string& username); // Displays details of a specific user
    
    static const std::string& getFilePath() { return FILE_PATH; }
};

#endif // USER_DATA_HANDLER_H
