#include <iostream>
#include "../include/dao/ItemListingHandler.h"
#include "../include/ui/WelcomeScreen.h"
#include <chrono>

int main() {
    // Initialize Item DAO
    ItemListingHandler itemDAO;

    // Check if items.dat exists and load items
    itemDAO.loadItems("data/items.dat");

    // If no items exist, generate and save a ton of items
    if (itemDAO.getAllItems().empty()) {
        std::cout << "No items found. Generating a ton of items...\n";

        auto now = std::chrono::system_clock::now();
        for (int i = 1; i <= 100; ++i) {
            std::string name = "Item" + std::to_string(i);
            std::string category = (i % 2 == 0) ? "Electronics" : "Books";
            std::string description = "This is " + name + " in the " + category + " category.";
            double startingBid = (i * 10) + 50; // Example starting bid logic
            double bidIncrement = 5.0;
            auto endTime = now + std::chrono::hours(24 + (i % 10)); // Randomized end time
            int minBuyerRating = 3;
            std::string sellerID = "seller" + std::to_string(i);

            // Create item and add it to the DAO
            Item newItem(name, category, description, startingBid, bidIncrement, endTime, minBuyerRating, sellerID);
            itemDAO.addItem(newItem);
        }

        // Save the items to the file
        itemDAO.saveItems("data/items.dat");
        std::cout << "100 items generated and saved to data/items.dat.\n";
    } else {
        std::cout << "Items already exist in data/items.dat.\n";
    }

    // Display all items to confirm
    std::cout << "=== All Items ===\n";
    itemDAO.displayItems(itemDAO.getAllItems());

    // Show the Welcome Screen
    WelcomeScreen welcomeScreen;
    welcomeScreen.displayMenu();

    return 0;
}
