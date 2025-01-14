// /include/utils/InputValidator.h
#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>
#include "../dao/userDataHandler.h"

class InputValidator {


public:
    // Boolean input validation
    static bool validateBoolean(const std::string& question);

    // String input validation
    static std::string validateString(const std::string& question);

    // Integer input validation
    static int validateInt(const std::string& question, int min, int max);

    // Double input validation
    static double validateDouble(const std::string& question, double min, double max);

    // User ID validation (e.g., u-1234)
    static std::string validateUserID(const std::string& question);

    // Date validation (format: yyyy-mm-dd)
    static std::string validateDate(const std::string& question);

    // Validation for a valid existing User ID
    static std::string validateExistingUserID(const std::string& question);

    static std::string validatePassword(const std::string& question);

    static bool isValidPassword(const std::string& password);



private:
    
    static UserDataHandler userDAO;
    
};

#endif // INPUTVALIDATOR_H
