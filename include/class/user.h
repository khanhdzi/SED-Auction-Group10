#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    double creditPoints;
    double buyerRating;
    double sellerRating;
    bool activeStatus;  // Renamed data member

public:
    User(const std::string& username, const std::string& password, const std::string& fullName, 
         const std::string& phoneNumber, const std::string& email, const std::string& idType, 
         const std::string& idNumber);

    bool validatePassword(const std::string& password);
    void updateProfile(const std::string& newPassword, const std::string& newPhoneNumber, 
                       const std::string& newEmail);
    void topUpCreditPoints(double amount);
    void deductCreditPoints(double amount);

    // Getter methods
    std::string getUsername() const;
    std::string getPassword() const;  // Added getter for password
    std::string getFullName() const;  // Added getter for fullName
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    std::string getIdType() const;
    std::string getIdNumber() const;
    double getCreditPoints() const;
    double getBuyerRating() const;
    double getSellerRating() const;
    bool getIsActive() const;  // Renamed getter method
    void setActive(bool active);
    // void topUpCreditPoints(double amount);
};

#endif
