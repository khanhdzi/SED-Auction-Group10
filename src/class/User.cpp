#include "../../include/class/user.h"
#include <iostream>

// Default Constructor
User::User() 
    : username(""), password(""), fullName(""), phoneNumber(""), 
      email(""), idType(""), idNumber(""), creditPoints(0.0), 
      buyerRating(0.0), sellerRating(0.0), activeStatus(true) {}

// Parameterized Constructor
User::User(const std::string& username, const std::string& password, 
           const std::string& fullName, const std::string& phoneNumber, 
           const std::string& email, const std::string& idType, 
           const std::string& idNumber)
    : username(username), password(password), fullName(fullName), 
      phoneNumber(phoneNumber), email(email), idType(idType), 
      idNumber(idNumber), creditPoints(0.0), buyerRating(0.0), 
      sellerRating(0.0), activeStatus(true) {}

// Getters
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getFullName() const { return fullName; }
std::string User::getPhoneNumber() const { return phoneNumber; }
std::string User::getEmail() const { return email; }
std::string User::getIdType() const { return idType; }
std::string User::getIdNumber() const { return idNumber; }
double User::getCreditPoints() const { return creditPoints; }
double User::getBuyerRating() const { return buyerRating; }
double User::getSellerRating() const { return sellerRating; }
bool User::isActive() const { return activeStatus; }

// Setters
void User::setPassword(const std::string& password) { this->password = password; }
void User::setFullName(const std::string& fullName) { this->fullName = fullName; }
void User::setPhoneNumber(const std::string& phoneNumber) { this->phoneNumber = phoneNumber; }
void User::setEmail(const std::string& email) { this->email = email; }
void User::setIdType(const std::string& idType) { this->idType = idType; }
void User::setIdNumber(const std::string& idNumber) { this->idNumber = idNumber; }
void User::setCreditPoints(double creditPoints) { this->creditPoints = creditPoints; }
void User::setBuyerRating(double buyerRating) { this->buyerRating = buyerRating; }
void User::setSellerRating(double sellerRating) { this->sellerRating = sellerRating; }
void User::setActiveStatus(bool activeStatus) { this->activeStatus = activeStatus; }

// Serialization Method (Binary Format)
void User::serialize(std::ofstream& file) const {
    size_t length;

    // Write username
    length = username.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(username.c_str(), length);

    // Write password
    length = password.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(password.c_str(), length);

    // Write fullName
    length = fullName.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(fullName.c_str(), length);

    // Write phoneNumber
    length = phoneNumber.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(phoneNumber.c_str(), length);

    // Write email
    length = email.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(email.c_str(), length);

    // Write idType
    length = idType.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(idType.c_str(), length);

    // Write idNumber
    length = idNumber.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(idNumber.c_str(), length);

    // Write other numeric and boolean fields
    file.write(reinterpret_cast<const char*>(&creditPoints), sizeof(creditPoints));
    file.write(reinterpret_cast<const char*>(&buyerRating), sizeof(buyerRating));
    file.write(reinterpret_cast<const char*>(&sellerRating), sizeof(sellerRating));
    file.write(reinterpret_cast<const char*>(&activeStatus), sizeof(activeStatus));
}

// Deserialization Method (Binary Format)
void User::deserialize(std::ifstream& file) {
    size_t length;
    char buffer[1024];  // Buffer for reading strings

    // Read username
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    username = buffer;

    // Read password
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    password = buffer;

    // Read fullName
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    fullName = buffer;

    // Read phoneNumber
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    phoneNumber = buffer;

    // Read email
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    email = buffer;

    // Read idType
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    idType = buffer;

    // Read idNumber
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    idNumber = buffer;

    // Read other numeric and boolean fields
    file.read(reinterpret_cast<char*>(&creditPoints), sizeof(creditPoints));
    file.read(reinterpret_cast<char*>(&buyerRating), sizeof(buyerRating));
    file.read(reinterpret_cast<char*>(&sellerRating), sizeof(sellerRating));
    file.read(reinterpret_cast<char*>(&activeStatus), sizeof(activeStatus));
}