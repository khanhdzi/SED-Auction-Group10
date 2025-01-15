// /src/utils/InputValidator.cpp
#include "../../include/utils/InputValidator.h"
#include <iostream>
#include <regex>
#include <limits>
#include <vector>
#include <ctime>
#include <sstream>

UserDataHandler InputValidator::userDAO;

bool InputValidator::validateBoolean(const std::string& question) {
    std::string answer;
    std::cout << question;
    std::cin >> answer;

    std::vector<std::string> validAnswers = {"true", "false", "t", "f", "yes", "no", "y", "n"};
    for (auto& c : answer) c = tolower(c);

    if (std::find(validAnswers.begin(), validAnswers.end(), answer) != validAnswers.end()) {
        return (answer == "true" || answer == "t" || answer == "yes" || answer == "y");
    } else {
        std::cout << "Invalid input. Please enter a valid boolean." << std::endl;
        return false;
    }
}

// Validate string input
std::string InputValidator::validateString(const std::string& question) {
    std::string input;

    while (true) {
        std::cout << question;

        // Clear the input stream before capturing input
        std::cin.clear();
        std::getline(std::cin, input);

        // Check for empty input
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please try again." << std::endl;
            continue;
        }

        return input;
    }
}

// Validate integer input within a given range
int InputValidator::validateInt(const std::string& question, int min, int max) {
    int value;
    while (true) {
        std::cout << question;
        std::cin >> value;

        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear(); // clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter an integer between " << min << " and " << max << "." << std::endl;
        } else {
            break;
        }
    }

    return value;
}

// Validate double input within a given range
double InputValidator::validateDouble(const std::string& question, double min, double max) {
    double value;
    while (true) {
        std::cout << question;
        std::cin >> value;

        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear(); // clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << std::endl;
        } else {
            break;
        }
    }

    return value;
}

// Validate User ID (format: u-1234)
std::string InputValidator::validateUserID(const std::string& question) {
    std::string userID;

    while (true) {
        std::cout << question;
        std::cin >> userID;

        std::regex userIDRegex("u-\\d{5}");
        if (!std::regex_match(userID, userIDRegex)) {
            std::cout << "Invalid User ID format. It should be 'u-XXXXX', where 'XXXXX' is a number." << std::endl;
            continue;
        }

        // Simulate a check for existing user ID (replace with actual logic)
        if (userID == "u-12345") {  // Simulate a user check
            std::cout << "User ID already exists. Please enter a different User ID." << std::endl;
            continue;
        }

        return userID;
    }
}

// Validate Date input (format: dd/mm/yyyy)
std::string InputValidator::validateDate(const std::string& question) {
    std::string date;
    std::regex dateRegex("\\d{2}/\\d{2}/\\d{4}");  // dd/mm/yyyy format

    while (true) {
        std::cout << question;
        std::cin >> date;

        if (!std::regex_match(date, dateRegex)) {
            std::cout << "Invalid date format. Please enter the date in 'dd/mm/yyyy' format." << std::endl;
            continue;
        }

        // Manually parse and validate the date
        int day, month, year;
        char separator1, separator2;

        std::istringstream dateStream(date);
        dateStream >> day >> separator1 >> month >> separator2 >> year;

        if (separator1 != '/' || separator2 != '/') {
            std::cout << "Invalid date format. Please enter the date in 'dd/mm/yyyy' format." << std::endl;
            continue;
        }

        // Validate the day, month, and year ranges
        if (month < 1 || month > 12) {
            std::cout << "Invalid month. Please enter a month between 01 and 12." << std::endl;
            continue;
        }

        if (day < 1 || day > 31) {
            std::cout << "Invalid day. Please enter a day between 01 and 31." << std::endl;
            continue;
        }

        // Validate the days in each month (handle leap years as well)
        bool validDate = true;
        switch (month) {
            case 2:
                if ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) && day > 29) {
                    validDate = false;  // Leap year February
                } else if (day > 28) {
                    validDate = false;  // Non-leap year February
                }
                break;
            case 4: case 6: case 9: case 11:
                if (day > 30) validDate = false;  // April, June, September, November have 30 days
                break;
            default:
                if (day > 31) validDate = false;  // Months with 31 days
                break;
        }

        if (!validDate) {
            std::cout << "Invalid date. Please check the day for the given month." << std::endl;
            continue;
        }

        return date;  // Valid date, return it
    }
}

// Validation for a valid existing User ID
std::string InputValidator::validateExistingUserID(const std::string& question) {
    std::string input;
    while (true) {
        input = validateUserID(question);  // Validate format first
        std::vector<User> users = userDAO.getAllUsers();
        bool exists = false;
        for (const auto& user : users) {
            if (user.getUsername() == input) {
                exists = true;
                break;
            }
        }
        if (exists) {
            return input;
        } else {
            std::cout << "User ID does not exist. Please try again.\n";
        }
    }
}
std::string InputValidator::validatePassword(const std::string& question) {
    std::string input;
    bool isValid = false;

    while (!isValid) {
        std::cout << question;
        std::getline(std::cin, input);

        if (isValidPassword(input)) {
            isValid = true;
        } else {
            std::cout << "Invalid password format. Password must be at least 8 characters long "
                     << "and contain only letters and numbers.\n";
        }
    }

    return input;
}

bool InputValidator::isValidPassword(const std::string& password) {
    // Check minimum length
    if (password.length() < 8) {
        return false;
    }

    // Check for alphanumeric characters only
    for (char c : password) {
        if (!std::isalnum(c)) {
            return false;
        }
    }

    return true;
}