#include "../include/controller/ItemDataController.h"
#include "../include/utils/InputValidator.h"
#include <iostream>

void ItemDataController::createItem() {
    // Get item details from user input
    std::string name = InputValidator::validateString("Enter item name: ");
    std::string category = InputValidator::validateString("Enter item category: ");
    std::string description = InputValidator::validateString("Enter item description: ");
    double startingBid = InputValidator::validateDouble("Enter starting bid: ", 0.0, 1e6);
    double bidIncrement = InputValidator::validateDouble("Enter bid increment: ", 1.0, 1e5);
    auto endTime = std::chrono::system_clock::now() + std::chrono::hours(InputValidator::validateInt("Enter auction duration in hours: ", 1, 168));

    // Create new item and add it to the DAO
    Item newItem(name, category, description, startingBid, bidIncrement, endTime, 3);
    itemDAO.addItem(newItem);
    std::cout << "Item created successfully: " << name << "\n";
}

void ItemDataController::editItem() {
    // Get item ID from user
    std::string itemId = InputValidator::validateString("Enter item ID to edit: ");

    // Check if item exists
    auto itemOpt = itemDAO.findItemById(itemId);
    if (!itemOpt) {
        std::cout << "Error: Item not found.\n";
        return;
    }

    // Get updated details from user
    std::string newDescription = InputValidator::validateString("Enter new description: ");
    double newStartingBid = InputValidator::validateDouble("Enter new starting bid: ", 0.0, 1e6);

    // Update the item
    if (itemDAO.editItem(itemId, newDescription, newStartingBid)) {
        std::cout << "Item updated successfully.\n";
    } else {
        std::cerr << "Error: Failed to update item.\n";
    }
}

void ItemDataController::deleteItem() {
    // Get item ID from user
    std::string itemId = InputValidator::validateString("Enter item ID to delete: ");

    // Attempt to delete the item
    if (itemDAO.removeItemById(itemId)) {
        std::cout << "Item deleted successfully.\n";
    } else {
        std::cerr << "Error: Item not found.\n";
    }
}

void ItemDataController::viewAllItems() const {
    auto items = itemDAO.getAllItems();
    if (items.empty()) {
        std::cout << "No items available.\n";
    } else {
        itemDAO.displayItems(items);
    }
}


void ItemDataController::searchItemsByCategory() const {
    std::string category = InputValidator::validateString("Enter category to search: ");
    auto items = itemDAO.searchItemsByCategory(category);
    if (items.empty()) {
        std::cout << "No items found in category: " << category << "\n";
        return;
    }
    itemDAO.displayItems(items);
}

void ItemDataController::searchItemsByKeyword() const {
    std::string keyword = InputValidator::validateString("Enter keyword to search: ");
    auto items = itemDAO.searchItemsByKeyword(keyword);
    if (items.empty()) {
        std::cout << "No items found with keyword: " << keyword << "\n";
        return;
    }
    itemDAO.displayItems(items);
}

void ItemDataController::sortItemsBy() const {
    std::string criteria = InputValidator::validateString("Enter sorting criteria (startingBid/endTime/currentBid): ");
    auto items = itemDAO.sortItemsBy(criteria);
    if (items.empty()) {
        std::cout << "No items to sort.\n";
        return;
    }
    itemDAO.displayItems(items);
}

void ItemDataController::saveListingsToFile() const {
    std::string filePath = InputValidator::validateString("Enter file path to save items: ");
    itemDAO.saveItems(filePath);
    std::cout << "Items saved successfully to " << filePath << ".\n";
}

void ItemDataController::loadListingsFromFile() {
    std::string filePath = InputValidator::validateString("Enter file path to load items: ");
    itemDAO.loadItems(filePath);
    std::cout << "Items loaded successfully from " << filePath << ".\n";
}