#include "../../include/dao/UserDataHandler.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>

void UserDataHandler::saveUsersToFile(const std::vector<User>& users, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Failed to open file for saving users: " + filename);
    }

    for (const auto& user : users) {
        serializeUser(user, outFile);
    }
    outFile.close();
}

std::vector<User> UserDataHandler::loadUsersFromFile(const std::string& filename) {
    std::vector<User> users;

    if (!std::filesystem::exists(filename)) {
        return users; // Return an empty vector if the file doesn't exist
    }

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Failed to open file for loading users: " + filename);
    }

    while (inFile.peek() != EOF) {
        users.push_back(deserializeUser(inFile));
    }
    inFile.close();

    return users;
}

void UserDataHandler::serializeUser(const User& user, std::ofstream& out) {
    out << user.getUsername() << '\n'
        << user.getPassword() << '\n'
        << user.getFullName() << '\n'
        << user.getPhoneNumber() << '\n'
        << user.getEmail() << '\n'
        << user.getIdType() << '\n'
        << user.getIdNumber() << '\n'
        << user.getCreditPoints() << '\n'
        << user.getBuyerRating() << '\n'
        << user.getSellerRating() << '\n'
        << user.getIsActive() << '\n';
}

User UserDataHandler::deserializeUser(std::ifstream& in) {
    std::string username, password, fullName, phoneNumber, email, idType, idNumber;
    double creditPoints, buyerRating, sellerRating;
    bool isActive;

    std::getline(in, username);
    std::getline(in, password);
    std::getline(in, fullName);
    std::getline(in, phoneNumber);
    std::getline(in, email);
    std::getline(in, idType);
    std::getline(in, idNumber);
    in >> creditPoints;
    in >> buyerRating;
    in >> sellerRating;
    in >> isActive;
    in.ignore(); // Ignore the newline after the boolean value

    User user(username, password, fullName, phoneNumber, email, idType, idNumber);
    user.topUpCreditPoints(creditPoints); // Set credit points
    user.setActive(isActive);             // Set active status
    return user;
}
