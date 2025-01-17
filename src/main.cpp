#include "../include/controller/ItemDataController.h"
#include "../include/utils/InputValidator.h"
#include <iostream>

int main() {
    // Initialize the ItemDataController
    ItemDataController controller;

    // Test creating items through the controller
    std::cout << "\n=== Creating Items ===\n";
    controller.createItem();
    controller.createItem();
    controller.createItem();

    // Test saving items to file
    std::cout << "\n=== Saving Items to File ===\n";
    controller.saveListingsToFile();
    std::cout << "Items saved successfully to data/items.dat\n";

    // Test loading items from file
    std::cout << "\n=== Loading Items from File ===\n";
    controller.loadListingsFromFile();

    // Test viewing all items
    std::cout << "\n=== Viewing All Items ===\n";
    controller.viewAllItems();

    // Test searching items by category
    std::cout << "\n=== Searching Items by Category ===\n";
    controller.searchItemsByCategory();

    // Test searching items by keyword
    std::cout << "\n=== Searching Items by Keyword ===\n";
    controller.searchItemsByKeyword();

    // Test sorting items by criteria
    std::cout << "\n=== Sorting Items ===\n";
    controller.sortItemsBy();

    // Test editing an item
    std::cout << "\n=== Editing an Item ===\n";
    controller.editItem();
    controller.viewAllItems();

    // Test deleting an item
    std::cout << "\n=== Deleting an Item ===\n";
    controller.deleteItem();
    controller.viewAllItems();

    return 0;
}
