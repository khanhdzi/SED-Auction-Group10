#include "../../include/ui/BidUI.h"
#include "../../include/class/Item.h"  
#include <iostream>
#include <limits>

BidUI::BidUI() {
    // Constructor, initializes the BidController
}

void BidUI::showBidMenu(const std::string& userId) {
    std::cout << "\n--- Bid Menu for User: " << userId << " ---\n";
    int choice;

    while (true) {
        std::cout << "\n--- Auction System ---\n";
        std::cout << "1. Place a bid\n";
        std::cout << "2. Search items\n";
        std::cout << "3. View item details\n";
        std::cout << "4. Exit\n";
        std::cout << "Please choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                placeBidMenu();
                break;
            case 2:
                searchItemsMenu();
                break;
            case 3:
                viewItemDetailsMenu();
                break;
            case 4:
                std::cout << "Exiting the auction system. Goodbye!\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void BidUI::placeBidMenu() {
    std::string itemId = getInputString("Enter the item ID to place a bid: ");
    std::string bidderId = getInputString("Enter your bidder ID: ");
    double bidAmount = getInputDouble("Enter your bid amount: ");

    if (bidController.placeBid(itemId, bidderId, bidAmount)) {
        std::cout << "Your bid has been placed successfully!\n";
    } else {
        std::cout << "Failed to place bid. Please check your bid details and try again.\n";
    }
}

void BidUI::searchItemsMenu() {
    std::string name = getInputString("Enter item name to search (or leave empty for all): ");
    std::string category = getInputString("Enter item category to search (or leave empty for all): ");
    double minPoints = getInputDouble("Enter minimum credit points (or 0 for no filter): ");
    double maxPoints = getInputDouble("Enter maximum credit points (or 0 for no filter): ");

    std::vector<Item> items = bidController.searchItems(name, category, minPoints, maxPoints);
    displayItems(items);
}

void BidUI::viewItemDetailsMenu() {
    std::string itemId = getInputString("Enter item ID to view details: ");
    bidController.viewItemDetails(itemId);
}

std::string BidUI::getInputString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin.ignore();  // Clear the newline character from previous input
    std::getline(std::cin, input);
    return input;
}

double BidUI::getInputDouble(const std::string& prompt) {
    double input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input, please enter a valid number.\n";
        } else {
            break;
        }
    }
    return input;
}

void BidUI::displayItems(const std::vector<Item>& items) {
    if (items.empty()) {
        std::cout << "No items found matching your search criteria.\n";
    } else {
        std::cout << "\n--- Search Results ---\n";
        for (const Item& item : items) {
            std::cout << "Item ID: " << item.getItemId() << "\n";
            std::cout << "Item Name: " << item.getName() << "\n";
            std::cout << "Price: " << item.getPrice() << "\n";
            std::cout << "Category: " << item.getCategory() << "\n";
            std::cout << "--------------------------------\n";
        }
    }
}
