#ifndef BID_UI_H
#define BID_UI_H

#include <string>
#include <vector>
#include "../controller/BidController.h"
#include "../class/Item.h"

class BidUI {
public:
    // Constructor that initializes the BidController
    BidUI();
    
    void showBidMenu(const std::string& userId);  // Declare this function

    // Display the main menu for bid-related actions
    void displayMenu();

    // Handle user input for placing a bid
    void placeBidMenu();

    // Handle user input for searching items
    void searchItemsMenu();

    // Display item details
    void viewItemDetailsMenu();

private:
    // BidController to handle bid-related logic
    BidController bidController;

    // Get user input for a string (e.g., item name, category)
    std::string getInputString(const std::string& prompt);

    // Get user input for a numeric value (e.g., bid amount)
    double getInputDouble(const std::string& prompt);

    // Display a list of search results
    void displayItems(const std::vector<Item>& items);
};

#endif
