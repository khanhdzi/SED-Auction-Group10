#include "../include/controller/UserService.h"
#include <iostream>

int main() {
    UserService userService;

    // Create and add users
    User user1("john_doe", "password123", "John Doe", "123-456-7890", "john@example.com", "ID", "12345");
    User user2("jane_smith", "securepass", "Jane Smith", "987-654-3210", "jane@example.com", "Passport", "67890");
    User user3("admin_user", "admin123", "Admin User", "555-555-5555", "admin@example.com", "DriverLicense", "11111");

    // Add users to the database
    if (userService.addUser(user1)) {
        std::cout << "User 'john_doe' added successfully.\n";
    } else {
        std::cout << "Failed to add user 'john_doe'.\n";
    }

    if (userService.addUser(user2)) {
        std::cout << "User 'jane_smith' added successfully.\n";
    } else {
        std::cout << "Failed to add user 'jane_smith'.\n";
    }

    if (userService.addUser(user3)) {
        std::cout << "User 'admin_user' added successfully.\n";
    } else {
        std::cout << "Failed to add user 'admin_user'.\n";
    }

    // List all users in the database
    std::cout << "\nCurrent Users in Database:\n";
    for (const auto& user : userService.getAllUsers()) {
        std::cout << "Username: " << user.getUsername()
                  << ", Full Name: " << user.getFullName()
                  << ", Email: " << user.getEmail()
                  << ", Phone: " << user.getPhoneNumber()
                  << ", ID Type: " << user.getIdType()
                  << ", ID Number: " << user.getIdNumber()
                  << ", Active: " << (user.getIsActive() ? "Yes" : "No") << "\n";
    }

    return 0;
}
