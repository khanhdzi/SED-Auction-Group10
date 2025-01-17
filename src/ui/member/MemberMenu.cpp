#include "../../../include/ui/member/MemberMenu.h"
#include "../../../include/controller/UserController.h"
#include "../../../include/class/Authenticator.h"
#include "../../../include/utils/utils.h"
#include "../../../include/utils/Category.h"
#include "../../../include/controller/BidController.h"
#include "../../../include/controller/ItemDataController.h"
#include "../../../include/utils/InputValidator.h"
#include <iostream>
#include <limits>

void MemberMenu::displayDashboard() {
    Utils::clearScreen();

    User* loggedUser = Authenticator::getLoggedUser();
    if (!loggedUser) {
        std::cout << "Error: No user is logged in.\n";
        return;
    }

    std::string username = loggedUser->getUsername();
    double accountBalance = loggedUser->getCreditPoints();

    // Fetch data for the dashboard
    ItemDataController itemController;
    BidController bidController;

    auto allItems =ItemDAO.getAllItems(); // Fetch all items
    auto activeBids = bidController.getActiveBidsForUser(username); // Fetch active bids
    auto activeListings = itemController.getItemsBySeller(username); // Fetch seller's listings

    // Dashboard Header
    std::cout << "====================================\n";
    std::cout << "          Account Dashboard         \n";
    std::cout << "====================================\n";
    std::cout << "Account Overview: " << username << "\n";
    std::cout << "----------------------------\n";
    std::cout << "Active Item Listings: " << activeListings.size()
              << " | Active Bids: " << activeBids.size() << "\n";
    std::cout << "Items Won to Date: 0"  // Placeholder: Update if you track won items
              << " | Account Balance: " << accountBalance << " CP\n";

    // Active Listings
    std::cout << "Your Active Item Listings\n";
    std::cout << "-------------------------\n";
    if (activeListings.empty()) {
        std::cout << "No active item listings.\n";
    } else {
        std::cout << "No. | Name          | Category     | Current Bid | Current Bidder | End Date & Time\n";
        for (size_t i = 0; i < activeListings.size(); ++i) {
            const auto& item = activeListings[i];
            auto endTimeT = std::chrono::system_clock::to_time_t(item.getEndTime());
            std::cout << i + 1 << "   | " << item.getName() << " | " << item.getCategory()
                      << " | " << (item.getCurrentBid() > 0 ? std::to_string(item.getCurrentBid()) : "No bids")
                      << " | " << (item.getCurrentBidder().empty() ? "No bidders" : item.getCurrentBidder())
                      << " | " << std::ctime(&endTimeT);
        }
    }

    // Active Bids
    std::cout << "Your Active Bids\n";
    std::cout << "----------------\n";
    if (activeBids.empty()) {
        std::cout << "No active bids.\n";
    } else {
        std::cout << "No. | Name           | Category     | Your Bid    | Current Bid    | End Date & Time\n";
        for (size_t i = 0; i < activeBids.size(); ++i) {
            const auto& bid = activeBids[i];
            auto itemOpt = ItemDAO.findItemById(bid.getItemId());
            if (!itemOpt) continue; // Skip if the item no longer exists

            const auto& item = *itemOpt;
            auto endTimeT = std::chrono::system_clock::to_time_t(item.getEndTime());
            std::cout << i + 1 << "   | " << item.getName() << " | " << item.getCategory()
                      << " | " << bid.getBidAmount() << " | " << item.getCurrentBid()
                      << " | " << std::ctime(&endTimeT);
        }
    }

    std::cout << "====================================\n\n";
}


void MemberMenu::displayMenu() {
    std::cout << "Debug: Entering Member Menu\n";

    int choice;

    do {
        displayDashboard();
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

        std::cout << "Debug: User selected " << choice << "\n";

        // Delegate to handleSelection
        handleSelection(choice);

    } while (choice != 4); // Exit when user chooses "Logout"

    std::cout << "Debug: Exiting Member Menu\n";
}





// Handle Menu Selections
void MemberMenu::handleSelection(int choice) {
    Utils::clearScreen();
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
    Utils::clearScreen();
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
void MemberMenu::displayBuyerFeaturesMenu() {
    BidController bidController;
    ItemDataController itemController;

    int choice;

    do {
        std::cout << "=== Buyer Features ===\n";
        std::cout << "1. Browse Items\n";
        std::cout << "2. View Bids for an Item\n";
        std::cout << "3. Place a Bid\n";
        std::cout << "4. View My Active Bids\n";
        std::cout << "5. Search Items by Category or Keyword\n";
        std::cout << "6. Sort Items\n";
        std::cout << "7. Top-Up Credit Points\n";
        std::cout << "8. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }

        std::cout << "Debug: User selected " << choice << "\n";

        Utils::clearScreen();

        switch (choice) {
            case 1: {
                std::cout << "Debug: Browsing items.\n";
                itemController.viewAllItems();
                break;
            }
            case 2: {
                std::cout << "Debug: Viewing bids for an item.\n";
                bidController.viewBidsForItem();
                break;
            }
            case 3: {
                itemController.viewAllItems();
                bidController.placeBid();
            
                break;
            }
            case 4: {
                std::cout << "Debug: Viewing user active bids.\n";
                bidController.viewUserBids();
                break;
            }
            case 5: {
                std::cout << "Debug: Searching items by category or keyword.\n";
                int searchChoice;
                std::cout << "Search Items:\n1. By Category\n2. By Keyword\nEnter choice: ";
                std::cin >> searchChoice;
                if (searchChoice == 1) {
                    std::cout << "Debug: Searching by category.\n";
                    Category::displayCategories();
                    itemController.searchItemsByCategory();
                } else if (searchChoice == 2) {
                    std::cout << "Debug: Searching by keyword.\n";
                    itemController.searchItemsByKeyword();
                } else {
                    std::cerr << "Invalid search choice.\n";
                }
                break;
            }
            case 6: {
                std::cout << "Debug: Sorting items.\n";
                itemController.sortItemsBy();
                break;
            }
            case 7: {
                std::cout << "Debug: Topping up credit points.\n";
                double amount = InputValidator::validateDouble("Enter the amount to top-up (CP): ", 0.01, 1e6);
                User* user = Authenticator::getLoggedUser();
                user->setCreditPoints(user->getCreditPoints() + amount);
                std::cout << "Top-up successful! Your new balance is " << user->getCreditPoints() << " CP.\n";
                break;
            }
            case 8: {
                std::cout << "Debug: Returning to Member Menu.\n";
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

void MemberMenu::displaySellerFeaturesMenu() {
    ItemDataController itemController;
    BidController bidController;

    int choice;

    do {
        std::cout << "=== Seller Features ===\n";
        std::cout << "1. Create Listing\n";
        std::cout << "2. Edit Listing\n";
        std::cout << "3. Remove Listing\n";
        std::cout << "4. View Listings\n";
        std::cout << "5. Finalize Auction\n";
        std::cout << "6. Return to Main Menu\n";
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
                itemController.createItem();
                 itemController.saveListingsToFile();
                break;
            case 2:
                itemController.editItem();
                 itemController.saveListingsToFile();
                break;
            case 3:
                itemController.deleteItem();
                 itemController.saveListingsToFile();
                break;
            case 4:
                itemController.viewAllItems();
                 itemController.saveListingsToFile();
                break;
            case 5: {
                // Add braces to isolate the scope of itemId
                std::string itemId = InputValidator::validateString("Enter the Item ID to finalize auction: ");
                bidController.finalizeAuction(itemId);
                break;
            }
            case 6:
                std::cout << "Returning to Main Menu...\n";
                return; // Exit the Seller Features menu
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        std::cout << "\nPress Enter to return to the Seller Features menu...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

    } while (true);
}
