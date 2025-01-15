//#include "RatingSystemDataHandler.h"
#include "../../include/DAO/RatingSystemDataHandler.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool RatingSystemDataHandler::loadRatings(unordered_map<string, User>& users,
                                           unordered_map<string, vector<int>>& buyerRatings,
                                           unordered_map<string, vector<int>>& sellerRatings) {
    ifstream file(FILENAME);
    if (!file) return false;

    string line, id, ratings;

    while (getline(file, line)) {
        id = line;
        User user(id);
        users[id] = user;

        getline(file, line);
        ratings = line.substr(6); // Skip "Buyer:"
        buyerRatings[id] = splitRatings(ratings);

        getline(file, line);
        ratings = line.substr(7); // Skip "Seller:"
        sellerRatings[id] = splitRatings(ratings);
    }

    file.close();
    return true;
}

void RatingSystemDataHandler::saveRatings(const unordered_map<string, User>& users,
                                          const unordered_map<string, vector<int>>& buyerRatings,
                                          const unordered_map<string, vector<int>>& sellerRatings) const {
    ofstream file(FILENAME);
    if (!file) {
        cerr << "Error saving ratings to file.\n";
        return;
    }

    for (const auto& [id, user] : users) {
        file << user.getUserID() << "\n";
        file << "Buyer:" << joinRatings(buyerRatings.at(id)) << "\n";
        file << "Seller:" << joinRatings(sellerRatings.at(id)) << "\n";
    }

    file.close();
    cout << "Ratings saved to file successfully.\n";
}

string RatingSystemDataHandler::joinRatings(const vector<int>& ratings) const {
    if (ratings.empty()) return "";
    stringstream ss;
    for (int rating : ratings) {
        ss << rating << " ";
    }
    string result = ss.str();
    result.pop_back(); // Remove trailing space
    return result;
}
