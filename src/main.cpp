#include "../include/dao/ItemListingHandler.h"
#include <iostream>
#include <chrono>

int main() {
    // Initialize the ItemListingHandler
    ItemListingHandler itemDAO;

    // Add test items to the DAO
    itemDAO.addItem(Item("Laptop", "Electronics", "High-performance laptop", 1000.0, 50.0, 
                         std::chrono::system_clock::now() + std::chrono::hours(48), 3));
    itemDAO.addItem(Item("Book: C++ Primer", "Books", "Comprehensive C++ book", 30.0, 5.0, 
                         std::chrono::system_clock::now() + std::chrono::hours(24), 3));
    itemDAO.addItem(Item("Jacket", "Fashion", "Warm winter jacket", 60.0, 10.0, 
                         std::chrono::system_clock::now() + std::chrono::hours(72), 3));

    // Save items to file
    std::cout << "\n=== Saving Items to File ===\n";
    itemDAO.saveItems("data/items.dat");
    std::cout << "Items saved successfully to data/items.dat\n";

    // Load items from file
    std::cout << "\n=== Loading Items from File ===\n";
    itemDAO.loadItems("data/items.dat");

    // Display all loaded items
    std::cout << "\n=== Displaying All Items ===\n";
    auto items = itemDAO.getAllItems();
    if (items.empty()) {
        std::cout << "No items available.\n";
    } else {
        itemDAO.displayItems(items);
    }

    return 0;
}