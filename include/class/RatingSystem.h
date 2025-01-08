// RatingSystem.h
#ifndef RATINGSYSTEM_H
#define RATINGSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <numeric>
#include <regex>

#define FILENAME "ratings.txt" // Data file

class User {
private:
    std::string userID;

public:
    User(std::string userID = "");

    std::string getUserID() const;
    void setUserID(const std::string& userID);
    std::string toString() const;
};

class RatingSystem {
private:
    std::unordered_map<std::string, std::vector<int>> buyerRatings;
    std::unordered_map<std::string, std::vector<int>> sellerRatings;
    std::unordered_map<std::string, User> users;

    void saveToFile() const;
    std::string joinRatings(const std::vector<int>& ratings) const;
    std::vector<int> splitRatings(const std::string& ratings) const;
    bool loadFromFile();
    bool isValidUserID(const std::string& userID) const;

public:
    RatingSystem();
    ~RatingSystem();

    void addUser();
    void addRating();
    void getAverageRating() const;
    void displayAllUsers() const;
};

void menu();

#endif // RATINGSYSTEM_H
