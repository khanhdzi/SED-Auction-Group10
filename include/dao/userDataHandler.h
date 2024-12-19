#ifndef USERDATAHANDLER_H
#define USERDATAHANDLER_H

#include "../class/user.h"
#include <vector>
#include <string>

class UserDataHandler {
public:
    // Method to save all users to a file
    static void saveUsersToFile(const std::vector<User>& users, const std::string& filename);

    // Method to load users from a file
    static std::vector<User> loadUsersFromFile(const std::string& filename);

private:
    // Helper methods to serialize and deserialize individual User objects
    static void serializeUser(const User& user, std::ofstream& out);
    static User deserializeUser(std::ifstream& in);
};

#endif
