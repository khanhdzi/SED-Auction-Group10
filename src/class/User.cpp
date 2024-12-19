#include "../../include/class/User.h"
#include <iostream>

// Constructor to initialize the user details
User::User(const std::string& username, const std::string& password, const std::string& fullName, 
           const std::string& phoneNumber, const std::string& email, const std::string& idType, 
           const std::string& idNumber)
    : username(username), password(password), fullName(fullName), phoneNumber(phoneNumber),
      email(email), idType(idType), idNumber(idNumber), creditPoints(0.0), 
      buyerRating(0.0), sellerRating(0.0), activeStatus(true) {}

// Getter methods
std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {  // Implemented getter for password
    return password;
}

std::string User::getFullName() const {  // Implemented getter for fullName
    return fullName;
}

std::string User::getPhoneNumber() const {
    return phoneNumber;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getIdType() const {
    return idType;
}

std::string User::getIdNumber() const {
    return idNumber;
}

double User::getCreditPoints() const {
    return creditPoints;
}

double User::getBuyerRating() const {
    return buyerRating;
}

double User::getSellerRating() const {
    return sellerRating;
}

bool User::getIsActive() const {
    return activeStatus;
}

// Set the user's active status
/* void User::setActive(bool active) {
    activeStatus = active;
}

void User::topUpCreditPoints(double amount) {
    
} */