#ifndef RATING_DATA_CONTROLLER_H
#define RATING_DATA_CONTROLLER_H

#include <string>
#include <vector>
#include <unordered_map>  // Required for unordered_map

// Forward declare User class (if User is defined elsewhere)
class User;  

// Include the necessary header for RatingSystemDataHandler
#include "../dao/RatingSystemDataHandler.h"  

class RatingDataController {
private:
    // Ensure 'std::' is used to specify the standard library types
    std::unordered_map<std::string, std::vector<int>> buyerRatings;
    std::unordered_map<std::string, std::vector<int>> sellerRatings;
    std::unordered_map<std::string, User> users;  // Ensure User is defined and properly included
    RatingSystemDataHandler dataHandler;

public:
    // Constructor
    RatingDataController();

    // Function declarations
    bool loadFromFile();
    void saveToFile() const;

    bool isValidUserID(const std::string& userID) const;
    bool addNewUser(const std::string& id);
    bool userExists(const std::string& id) const;

    void addRating(const std::string& id, int rating, bool isBuyer);
    double getAverageRating(const std::string& id, bool isBuyer) const;

    void displayUsers() const;
};

#endif // RATING_DATA_CONTROLLER_H
