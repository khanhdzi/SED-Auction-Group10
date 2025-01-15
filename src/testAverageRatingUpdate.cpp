#include <iostream>
#include "../include/dao/UserDataHandler.h"

void displayAllUsers() {
    UserDataHandler userHandler;

    // Retrieve all users
    std::vector<User> users = userHandler.getAllUsers();

    if (users.empty()) {
        std::cout << "No users found in the file.\n";
        return;
    }

    std::cout << "Displaying all users:\n";
    std::cout << "---------------------\n";

    // Display user details
    for (const auto& user : users) {
        std::cout << "Username: " << user.getUsername() << "\n"
                  << "Full Name: " << user.getFullName() << "\n"
                  << "Phone Number: " << user.getPhoneNumber() << "\n"
                  << "Email: " << user.getEmail() << "\n"
                  << "Buyer Rating: " << user.getBuyerRating() << "\n"
                  << "Seller Rating: " << user.getSellerRating() << "\n"
                  << "---------------------\n";
    }
}

void displaySpecificUser(const std::string& username) {
    UserDataHandler userHandler;

    // Use the displayUserDetails method to show details for a specific user
    std::cout << "Fetching details for username: " << username << "\n";
    userHandler.displayUserDetails(username);
}

int main() {
    // Display all users
    std::cout << "Displaying all users:\n";
    displayAllUsers();

    // Display a specific user
    std::string username;
    std::cout << "\nEnter a username to fetch details: ";
    std::cin >> username;
    displaySpecificUser(username);

    return 0;
}
