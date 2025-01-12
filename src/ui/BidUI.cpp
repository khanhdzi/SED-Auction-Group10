#include "../../include/ui/BidUI.h"
#include <iostream>

void BidUI::showBidMenu(const std::string& userId) {
    std::cout << "\nBidding Menu for user: " << userId << "\n";
    std::cout << "1. Search Items\n";
    std::cout << "2. Place Bid\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        searchItems(userId);
    } else if (choice == 2) {
        placeBid(userId);
    } else {
        std::cout << "Returning to Main Menu...\n";
    }
}

void BidUI::searchItems(const std::string& userId) {
    std::cout << "Searching items for user: " << userId << std::endl;
}

void BidUI::placeBid(const std::string& userId) {
    std::cout << "Placing bid for user: " << userId << std::endl;
}
