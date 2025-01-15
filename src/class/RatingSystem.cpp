

//#include "RatingSystem.h"
#include "../../include/class/RatingSystem.h"

#include <iostream>

using namespace std;

RatingSystem::RatingSystem() {
    if (!dataController.loadFromFile()) {
        cout << "No existing data found. Starting fresh.\n";
    }
}

RatingSystem::~RatingSystem() {
    dataController.saveToFile();
}

void RatingSystem::addUser() {
    string id;

    cout << "Enter User ID (format: UXXXX): ";
    cin >> id;

    if (!dataController.isValidUserID(id)) {
        cout << "Invalid User ID format. Must be in the format UXXXX (e.g., U1234).\n";
        return;
    }

    if (!dataController.addNewUser(id)) {
        cout << "User ID already exists.\n";
        return;
    }

    cout << "User added successfully with default ratings.\n";
}

void RatingSystem::addRating() {
    string id;
    int rating;
    bool isBuyer;

    cout << "Enter User ID: ";
    cin >> id;

    if (!dataController.userExists(id)) {
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

    dataController.addRating(id, rating, isBuyer);
    cout << "Rating added successfully.\n";
}

void RatingSystem::getAverageRating() const {
    string id;
    bool isBuyer;

    cout << "Enter User ID: ";
    cin >> id;

    if (!dataController.userExists(id)) {
        cout << "User not found.\n";
        return;
    }

    cout << "Get Buyer rating? (1 for Yes, 0 for No): ";
    cin >> isBuyer;

    double avg = dataController.getAverageRating(id, isBuyer);
    cout << "Average Rating as " << (isBuyer ? "Buyer" : "Seller") << ": " << fixed << setprecision(2) << avg << "\n";
}

void RatingSystem::displayAllUsers() const {
    dataController.displayUsers();
}
