// RatingSystem.cpp
#include "RatingSystem.h"
#include <fstream>
#include <iomanip>

using namespace std;

// User class implementation
User::User(string userID) : userID(userID) {}

string User::getUserID() const {
    return userID;
}

void User::setUserID(const string& userID) {
    this->userID = userID;
}

string User::toString() const {
    return userID;
}

// RatingSystem class implementation
RatingSystem::RatingSystem() {
    if (!loadFromFile()) {
        cout << "No existing data found. Starting fresh.\n";
    }
}

RatingSystem::~RatingSystem() {
    saveToFile();
}

void RatingSystem::saveToFile() const {
    ofstream file(FILENAME);
    if (!file) {
        cerr << "Error saving ratings to file.\n";
        return;
    }

    for (const auto& [id, user] : users) {
        file << user.toString() << "\n";
        file << "Buyer:" << joinRatings(buyerRatings.at(id)) << "\n";
        file << "Seller:" << joinRatings(sellerRatings.at(id)) << "\n";
    }

    file.close();
    cout << "Ratings saved to file successfully.\n";
}

string RatingSystem::joinRatings(const vector<int>& ratings) const {
    if (ratings.empty()) return "";
    string result = "";
    for (int rating : ratings) {
        result += to_string(rating) + " ";
    }
    result.pop_back();
    return result;
}

vector<int> RatingSystem::splitRatings(const string& ratings) const {
    vector<int> result;
    size_t start = 0, end;
    while ((end = ratings.find(" ", start)) != string::npos) {
        result.push_back(stoi(ratings.substr(start, end - start)));
        start = end + 1;
    }
    if (start < ratings.size()) {
        result.push_back(stoi(ratings.substr(start)));
    }
    return result;
}

bool RatingSystem::loadFromFile() {
    ifstream file(FILENAME);
    if (!file) return false;

    string line, id, ratings;

    while (getline(file, line)) {
        id = line;
        User user(id);
        users[id] = user;

        getline(file, line);
        ratings = line.substr(6);
        buyerRatings[id] = splitRatings(ratings);

        getline(file, line);
        ratings = line.substr(7);
        sellerRatings[id] = splitRatings(ratings);
    }

    file.close();
    return true;
}

bool RatingSystem::isValidUserID(const string& userID) const {
    return regex_match(userID, regex("U\\d{4}"));
}

void RatingSystem::addUser() {
    string id;

    cout << "Enter User ID (format: UXXXX): ";
    cin >> id;

    if (!isValidUserID(id)) {
        cout << "Invalid User ID format. Must be in the format UXXXX (e.g., U1234).\n";
        return;
    }

    if (users.count(id)) {
        cout << "User ID already exists.\n";
        return;
    }

    User user(id);
    users[id] = user;
    buyerRatings[id] = {3};
    sellerRatings[id] = {3};

    cout << "User added successfully with default ratings.\n";
}

void RatingSystem::addRating() {
    string id;
    int rating;
    bool isBuyer;

    cout << "Enter User ID: ";
    cin >> id;

    if (!users.count(id)) {
        cout << "User not found. Please add the user first.\n";
        return;
    }

    cout << "Enter Rating (1-5): ";
    cin >> rating;

    if (rating < 1 || rating > 5) {
        cout << "Invalid rating. Must be between 1 and 5.\n";
        return;
    }

    cout << "Is this a Buyer rating? (1 for Yes, 0 for No): ";
    cin >> isBuyer;

    if (isBuyer) {
        buyerRatings[id].push_back(rating);
    } else {
        sellerRatings[id].push_back(rating);
    }

    cout << "Rating added successfully.\n";
}

void RatingSystem::getAverageRating() const {
    string id;
    bool isBuyer;

    cout << "Enter User ID: ";
    cin >> id;

    if (!users.count(id)) {
        cout << "User not found.\n";
        return;
    }

    cout << "Get Buyer rating? (1 for Yes, 0 for No): ";
    cin >> isBuyer;

    const vector<int>& ratings = isBuyer ? buyerRatings.at(id) : sellerRatings.at(id);

    double avg = accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
    cout << "Average Rating as " << (isBuyer ? "Buyer" : "Seller") << ": " << fixed << setprecision(2) << avg << "\n";
}

void RatingSystem::displayAllUsers() const {
    if (users.empty()) {
        cout << "No users available.\n";
        return;
    }

    for (const auto& [id, user] : users) {
        cout << "User ID: " << user.getUserID() << "\n";
        cout << "Buyer Ratings: " << joinRatings(buyerRatings.at(id)) << "\n";
        cout << "Seller Ratings: " << joinRatings(sellerRatings.at(id)) << "\n";
    }
}

// Menu implementation
void menu() {
    cout << "\nRating System Menu\n";
    cout << "1. View All Users\n";
    cout << "2. Add User\n";
    cout << "3. Add Rating\n";
    cout << "4. Get Average Rating\n";
    cout << "5. Exit\n";
}
