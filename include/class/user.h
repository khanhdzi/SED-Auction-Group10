#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>  // For file stream operations

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
    double buyerRating;  // Direct buyer rating set
    double sellerRating; // Direct seller rating set
    int buyerRatingCount; // Number of buyer ratings
    int sellerRatingCount; // Number of seller ratings
    bool activeStatus;

public:
    // Default Constructor
    User();

    // Parameterized Constructor
    User(const std::string& username, const std::string& password, const std::string& fullName,
         const std::string& phoneNumber, const std::string& email, const std::string& idType,
         const std::string& idNumber);

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    std::string getIdType() const;
    std::string getIdNumber() const;
    double getCreditPoints() const;
    double getBuyerRating() const;  // Average buyer rating
    double getSellerRating() const; // Average seller rating
    bool isActive() const;

    // Setters
    void setPassword(const std::string& password);
    void setFullName(const std::string& fullName);
    void setPhoneNumber(const std::string& phoneNumber);
    void setEmail(const std::string& email);
    void setIdType(const std::string& idType);
    void setIdNumber(const std::string& idNumber);
    void setCreditPoints(double creditPoints);
    void setBuyerRating(double buyerRating); // Manually set buyer rating
    void setSellerRating(double sellerRating); // Manually set seller rating
    void setActiveStatus(bool activeStatus);

    // Add ratings
    void addBuyerRating(double rating);  // Add and calculate average buyer rating
    void addSellerRating(double rating); // Add and calculate average seller rating

    // Methods for Serialization
    void serialize(std::ofstream& file) const;  // Serialize user to file
    void deserialize(std::ifstream& file);      // Deserialize user from file
};

#endif // USER_H
