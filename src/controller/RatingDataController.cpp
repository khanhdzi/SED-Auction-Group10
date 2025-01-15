//#include "RatingDataController.h"
#include "../../include/controller/RatingDataController.h"

#include <iostream>
#include <numeric>
#include <iomanip>

using namespace std;

RatingDataController::RatingDataController() {
    // Constructor logic if necessary
}

bool RatingDataController::loadFromFile() {
    return dataHandler.loadRatings(users, buyerRatings, sellerRatings);
}

void RatingDataController::saveToFile() const {
    dataHandler.saveRatings(users, buyerRatings, sellerRatings);
}

bool RatingDataController::isValidUserID(const string& userID) const {
    return regex_match(userID, regex("U\\d{4}"));
}

bool RatingDataController::addNewUser(const string& id) {
    if (users.count(id)) return false;

    User user(id);
    users[id] = user;
    buyerRatings[id] = {3}; // Default rating
    sellerRatings[id] = {3}; // Default rating;

    return true;
}

bool RatingDataController::userExists(const string& id) const {
    return users.count(id);
}

void RatingDataController::addRating(const string& id, int rating, bool isBuyer) {
    if (isBuyer) {
        buyerRatings[id].push_back(rating);
    } else {
        sellerRatings[id].push_back(rating);
    }
}

double RatingDataController::getAverageRating(const string& id, bool isBuyer) const {
    const vector<int>& ratings = isBuyer ? buyerRatings.at(id) : sellerRatings.at(id);
    return accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
}

void RatingDataController::displayUsers() const {
    if (users.empty()) {
        cout << "No users available.\n";
        return;
    }

    for (const auto& [id, user] : users) {
        cout << "User ID: " << user.getUserID() << "\n";
        cout << "Buyer Ratings: " << dataHandler.joinRatings(buyerRatings.at(id)) << "\n";
        cout << "Seller Ratings: " << dataHandler.joinRatings(sellerRatings.at(id)) << "\n";
    }
}
