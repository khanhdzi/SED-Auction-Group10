#include "../../include/controller/ItemDataController.h"
#include "../../include/utils/InputValidator.h"
#include "../../include/utils/Category.h"
#include <iostream>
#include <stdexcept>

// Create a new item listing interactively
void ItemDataController::createItemListing() const {
    std::string name = InputValidator::validateString("Enter item name: ");
    std::string category = InputValidator::validateString("Enter category: ");
    if (!Category::isValidCategory(category)) {
        throw std::invalid_argument("Invalid category: " + category);
    }
    std::string description = InputValidator::validateString("Enter description: ");
    double startingBid = InputValidator::validateDouble("Enter starting bid: ", 0.0, 1e6);
    double bidIncrement = InputValidator::validateDouble("Enter bid increment: ", 1.0, 1e5);
    auto endTime = std::chrono::system_clock::now() + std::chrono::hours(24);

    createItemListing(name, category, description, startingBid, bidIncrement, endTime);
}

// Create a new item listing directly
void ItemDataController::createItemListing(const std::string& name, const std::string& category, 
                                           const std::string& description, double startingBid, 
                                           double bidIncrement, std::chrono::system_clock::time_point endTime) const {
    if (!Category::isValidCategory(category)) {
        throw std::invalid_argument("Invalid category: " + category);
    }

    Item newItem(name, category, description, startingBid, bidIncrement, endTime, 0);
    ItemDAO.addItem(newItem);
    std::cout << "Item created successfully: " << name << "\n";
}

// View all item listings
void ItemDataController::viewListings() const {
    auto items = ItemDAO.getAllItems();
    if (items.empty()) {
        std::cout << "No items available.\n";
        return;
    }

    for (size_t i = 0; i < items.size(); ++i) {
        const auto& item = items[i];
        std::cout << i + 1 << ". " << item.getName() << " | " << item.getCategory()
                  << " | Starting Bid: $" << item.getStartingBid() << "\n";
    }
}

std::optional<Item> ItemListingHandler::findItemById(const std::string& itemId) const {
    for (const auto& item : items) {
        if (item.getName() == itemId) { // Assuming item name is the unique identifier
            return item;
        }
    }
    return std::nullopt;
}


// Save item listings to file
void ItemDataController::saveListingsToFile(const std::string& filePath) const {
    ItemDAO.saveItems(filePath);
}

// Load item listings from file
void ItemDataController::loadListingsFromFile(const std::string& filePath) {
    ItemDAO.loadItems(filePath);
}