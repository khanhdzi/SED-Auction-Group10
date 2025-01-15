#include "../include/utils/Category.h"
#include "../include/dao/ItemListingHandler.h"
#include "../include/controller/ItemDataController.h"
#include <iostream>
#include <chrono>

int main() {
    // Initialize categories
    Category::loadFromFile("data/categories.dat"); // Load from default file

    // Add hardcoded categories
    Category::addCategory("Electronics");
    Category::addCategory("Books");
    Category::addCategory("Home Appliances");

    // Save categories to file
    Category::saveToFile("data/categories.dat");

    // List all categories
    std::cout << "--- Categories ---\n";
    Category::listCategories();

    // Initialize item data controller
    ItemDataController itemController;

    // Create hardcoded items
    auto endTime = std::chrono::system_clock::now() + std::chrono::hours(24); // 24 hours from now
    try {
        // Use createItemListing with no arguments (interactive creation)
        std::cout << "Please create an item interactively:\n";
        itemController.createItemListing();

        // Save items to file
        itemController.saveListingsToFile("data/items.dat");

        // View all items
        std::cout << "\n--- Item Listings ---\n";
        itemController.viewListings();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
