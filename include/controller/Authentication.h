#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "../class/User.h"
#include "../dao/UserDataHandler.h"
#include <vector>
#include <optional>
#include <string>

class Authentication {
public:
    Authentication();
    
    // Login methods
    std::optional<User> login(const std::string& username, const std::string& password);
    
    // Registration methods
    bool registerUser(const std::string& username, const std::string& password,
                     const std::string& fullName, const std::string& phoneNumber,
                     const std::string& email, const std::string& idType,
                     const std::string& idNumber);
    
    // Helper methods
    bool isUsernameAvailable(const std::string& username);
    bool validateLoginCredentials(const std::string& username, const std::string& password);

private:
    std::vector<User> users;
    static const std::string USER_DATA_FILE;
    
    void loadUsers();
    void saveUsers();
    bool isValidPassword(const std::string& password);
};

#endif