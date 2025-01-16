#include "../../../include/ui/member/MemberMenu.h"
#include "../../../include/controller/UserController.h"
#include "../../../include/class/Authenticator.h"
#include "../../../include/utils/utils.h"
#include "../../../include/controller/BidController.h"
#include "../../../include/controller/ItemDataController.h"
#include "../../../include/utils/InputValidator.h"
#include <iostream>
#include <limits>


void MemberMenu::displayDashboard() {
    Utils::clearScreen();
    std::cout << "====================================\n";
    std::cout << "          Account Dashboard         \n";
    std::cout << "====================================\n";
    std::cout << "Account Overview: Member123\n"; // Replace with actual member username
    std::cout << "------------------------------------\n";
    std::cout << "Active Item Listings: 3  |  Active Bids: 2\n";
    std::cout << "Items Won to Date: 1     |  Account Balance: 300 CP\n";
    std::cout << "------------------------------------\n\n";
    std::cout << "Your Active Item Listings:\n";
    std::cout << "------------------------------------\n";
    std::cout << "No. | Name          | Category     | Current Bid | Current Bidder | End Date & Time\n";
    std::cout << "1   | iPhone 13 Pro | Electronics  | 350         | Member456      | 16/01/2025 18:00\n";
    std::cout << "2   | Rare Coin Set | Collectibles | 300         | Member789      | 20/01/2025 09:00\n";
    std::cout << "------------------------------------\n\n";
    std::cout << "Your Active Bids:\n";
    std::cout << "------------------------------------\n";
    std::cout << "No. | Name           | Category     | Your Bid    | Current Bid    | End Date & Time\n";
    std::cout << "1   | Sony Headphones| Electronics  | 100         | 250            | 20/01/2025 10:00\n";
    std::cout << "2   | Road Bike      | Vehicles     | 300         | 310            | 23/01/2025 17:30\n";
    std::cout << "====================================\n\n";
}
// Display Main Member Menu
void MemberMenu::displayMenu() {
    int choice;
    displayDashboard(); // Show dashboard before the menu

    do {
        std::cout << "=== Member Menu ===\n";
        std::cout << "1. General Features\n";
        std::cout << "2. Buyer Features\n";
        std::cout << "3. Seller Features\n";
        std::cout << "4. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue;
        }

        handleSelection(choice);

    } while (choice != 4); // Exit when user logs out
}

// Handle Menu Selections
void MemberMenu::handleSelection(int choice) {
    switch (choice) {
        case 1:
            displayGeneralFeaturesMenu();
            break;
        case 2:
            displayBuyerFeaturesMenu();
            break;
        case 3:
            displaySellerFeaturesMenu();
            break;
        case 4:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

// General Features Menu
void MemberMenu::displayGeneralFeaturesMenu() {
    UserController userController; // Declare UserController instance
    int choice;

    do {
        std::cout << "=== General Features ===\n";
        std::cout << "1. View Profile\n";
        std::cout << "2. Edit Profile\n";
        std::cout << "3. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }
        Utils::clearScreen();
        switch (choice) {
            case 1:
                viewProfile(userController);
                break;
            case 2:
                editProfile(userController);
                break;
            case 3:
                Utils::clearScreen();
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (true);
}


void MemberMenu::viewProfile(UserController& userController) {
    if (authenticator.isLoggedIn()) {
        // Directly get the username of the logged-in user
        userController.displayUserInfo(authenticator.getLoggedUser()->getUsername());
    } else {
        std::cout << "You are not logged in. Please log in to view your profile.\n";
    }
}

void MemberMenu::editProfile(UserController& userController) {
    if (authenticator.isLoggedIn()) {
        User* loggedUser = authenticator.getLoggedUser();

        // Call UserController's editProfile
        userController.editProfile(*loggedUser);

        // Prompt to return
        std::cout << "Profile updated successfully.\n";
        std::cout << "Press Enter to return to the General Features menu...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer before waiting
        std::cin.get(); // Wait for Enter key
    } else {
        std::cout << "You are not logged in. Please log in to edit your profile.\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer before waiting
        std::cin.get(); // Wait for Enter key
    }
}



// Buyer Features Menu
void MemberMenu::displayBuyerFeaturesMenu() {
    BidController bidController;               // Instance of BidController
    ItemDataController itemController;         // Instance of ItemDataController
    int choice;

    do {
        std::cout << "=== Buyer Features ===\n";
        std::cout << "1. Browse Items\n";
        std::cout << "2. View Bids for an Item\n";
        std::cout << "3. Place a Bid\n";
        std::cout << "4. View My Active Bids\n";
        std::cout << "5. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        Utils::clearScreen();

        switch (choice) {
            case 1: {
                // Browse items
                itemController.viewListings();
                break;
            }
            case 2: {
                // View bids for a specific item
                std::string itemId = InputValidator::validateString("Enter the Item ID to view bids: ");
                bidController.viewBidsForItem(itemId);
                break;
            }
            case 3: {
                // Place a bid
                std::string itemId = InputValidator::validateString("Enter the Item ID to bid on: ");
                double bidAmount = InputValidator::validateDouble("Enter your bid amount: ", 0.01, 1e6);
                double bidLimit = InputValidator::validateDouble("Enter your automatic bid limit (0 for none): ", 0.0, 1e6);
                bidController.placeBid(itemId, bidAmount, bidLimit);
                break;
            }
            case 4: {
                // View active bids
                bidController.viewUserBids();
                break;
            }
            case 5: {
                // Return to Main Menu
                return;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }

        std::cout << "\nPress Enter to return to the Buyer Features menu...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

    } while (true);
}

// Seller Features Menu
void MemberMenu::displaySellerFeaturesMenu() {
    ItemDataController itemController; // Create the controller instance
    int choice;
    do {
        std::cout << "=== Seller Features ===\n";
        std::cout << "1. Create Listing\n";
        std::cout << "2. Edit Listing\n";
        std::cout << "3. Remove Listing\n";
        std::cout << "4. View Listings\n"; // Optional: Add to allow viewing
        std::cout << "5. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                Utils::clearScreen();
                try {
                    itemController.createItemListing();
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            case 2:
                Utils::clearScreen();
                std::cout << "Feature not implemented yet: Edit Listing.\n";
                break;
            case 3:
                Utils::clearScreen();
                std::cout << "Feature not implemented yet: Remove Listing.\n";
                break;
            case 4:
                Utils::clearScreen();
                itemController.viewListings();
                break;
            case 5:
                Utils::clearScreen();
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (true);
}



