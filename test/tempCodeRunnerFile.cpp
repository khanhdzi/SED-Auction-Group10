#include <iostream>
#include <string>
#include "Auction.h"
#include "User.h"
using namespace std;

void auctionMenu(User &loggedInUser) {
    Auction auction;

    // Add sample items to the auction
    auction.addItem(Item("item1", "Laptop", "High-end gaming laptop", 500));
    auction.addItem(Item("item2", "Phone", "Latest smartphone", 300));

    int choice;
    do {
        cout << "\n--- Auction Menu ---\n";
        cout << "1. List Items\n";
        cout << "2. Place Bid\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            auction.listItems();
            break;
        }
        case 2: {
            string itemID;
            double bidAmount;
            cout << "Enter Item ID: ";
            cin >> itemID;
            cout << "Enter your bid amount: ";
            cin >> bidAmount;

            Item* item = auction.getItemByID(itemID);
            if (item) {
                if (bidAmount <= item->getHighestBid()) {
                    cout << "Bid must be higher than the current highest bid of " << item->getHighestBid() << "!\n";
                } else {
                    item->placeBid(loggedInUser.getUsername(), bidAmount);
                    cout << "Bid placed successfully!\n";
                }
            } else {
                cout << "Item not found!\n";
            }
            break;
        }
        case 3: {
            cout << "Exiting the auction menu. Goodbye!\n";
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

int main() {
    User loggedInUser("user1", "pass123", "User One", "1234567890", "user1@example.com", 100.0);
    auctionMenu(loggedInUser);
    return 0;
}

