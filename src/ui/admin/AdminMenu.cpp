#include "../../../include/ui/admin/AdminMenu.h"
#include <iostream>
#include <limits>
#include <iomanip> 
#include <unordered_map> 
#include <algorithm>   
#include "../../../include/utils/utils.h"
#include "../../../include/controller/UserController.h"
#include "../../../include/controller/ItemDataController.h"
#include "../../../include/utils/InputValidator.h"

void AdminMenu::displayMenu() {
    int choice;
    do {
        Utils::clearScreen();
        std::cout << "=== Admin Menu ===\n";
        std::cout << "1. Manage Users Menu\n";
        std::cout << "2. Statistics Menu\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        handleSelection(choice);

    } while (choice != 3); // Exit the menu when the user selects Logout
}

void AdminMenu::handleSelection(int choice) {
    switch (choice) {
        case 1:
            manageUsersMenu();
            break;
        case 2:
            statisticsMenu();
            break;
        case 3:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

void AdminMenu::manageUsersMenu() {
    UserController userController;
    int choice;

    do {
        Utils::clearScreen();
        std::cout << "=== Manage Users Menu ===\n";
        std::cout << "1. View All Users\n";
        std::cout << "2. View Specific User Info\n";
        std::cout << "3. Create New User\n";
        std::cout << "4. Edit User\n";
        std::cout << "5. Delete User\n";
        std::cout << "6. Return to Admin Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        Utils::clearScreen();
        switch (choice) {
            case 1:
                userController.displayAllUsers();
                break;
            case 2: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string username = InputValidator::validateString("Enter username to view: ");
                userController.displayUserInfo(username);
                break;
            }
            case 3:
                userController.createUser();
                break;
            case 4: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string username = InputValidator::validateString("Enter username to edit: ");
                auto users = userController.getAllUsers();
                for (auto& user : users) {
                    if (user.getUsername() == username) {
                        userController.editProfile(user);
                        break;
                    }
                }
                break;
            }
            case 5: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string username = InputValidator::validateString("Enter username to delete: ");
                userController.deleteUser(username);
                break;
            }
            case 6:
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    } while (true);
}

void AdminMenu::statisticsMenu() {
    UserController userController;
    ItemDataController itemController;

    auto users = userController.getAllUsers();
    auto items = itemController.getAllItems();

    int totalUsers = users.size();
    int totalItems = items.size();
    int activeItems = std::count_if(items.begin(), items.end(), [](const Item& item) {
        return item.getStatus() == "active";
    });
    int closedItems = totalItems - activeItems;

    std::cout << "=== Statistics Menu ===\n";
    std::cout << "Total Users: " << totalUsers << "\n";
    std::cout << "Total Items Listed: " << totalItems << "\n";
    std::cout << "Active Items: " << activeItems << "\n";
    std::cout << "Closed Items: " << closedItems << "\n";

    std::cout << "\nTop Sellers by Listings:\n";
    std::unordered_map<std::string, int> sellerCount;
    for (const auto& item : items) {
        sellerCount[item.getSellerID()]++;
    }

    for (const auto& [seller, count] : sellerCount) {
        std::cout << "Seller: " << seller << " | Listings: " << count << "\n";
    }

    std::cout << "\nPress Enter to return to the Admin Menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
