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
    static const std::string& getFilePath() { return FILE_PATH; }
};

#endif // USER_DATA_HANDLER_H
