#include "User.h"

User::User(string username, string password, string fullName, string phoneNumber, string email)
    : username(username), password(password), fullName(fullName),
      phoneNumber(phoneNumber), email(email), creditPoints(0.0),
      averageRating(5.0), ratingCount(1) {}

void User::displayProfile() {
    cout << "\n--- User Profile ---\n";
    cout << "Username: " << username << endl;
    cout << "Full Name: " << fullName << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Email: " << email << endl;
    cout << "Credit Points: " << creditPoints << endl;
    cout << "Average Rating: " << averageRating << endl;
}

bool User::updateProfile() {
    cout << "Update Full Name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Update Phone Number: ";
    getline(cin, phoneNumber);

    cout << "Update Email: ";
    getline(cin, email);

    cout << "Profile updated successfully!" << endl;
    return true;
}

bool User::updatePassword(const string &oldPassword, const string &newPassword) {
    if (password != oldPassword) {
        cout << "Old password incorrect!" << endl;
        return false;
    }

    password = newPassword;
    cout << "Password updated successfully!" << endl;
    return true;
}

void User::topUpCredits(double amount) {
    creditPoints += amount;
    cout << "Credits topped up successfully!" << endl;
}

double User::getCredits() const {
    return creditPoints;
}

void User::addRating(double rating) {
    averageRating = ((averageRating * ratingCount) + rating) / (ratingCount + 1);
    ratingCount++;
}

double User::getAverageRating() const {
    return averageRating;
}

string User::getUsername() const {
    return username;
}

bool User::authenticate(const string &password) const {
    return this->password == password;
}
