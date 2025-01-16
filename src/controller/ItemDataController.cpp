#include "../../include/controller/ItemDataController.h"
#include "../../include/utils/InputValidator.h"
#include "../../include/utils/Category.h"
#include <iostream>
#include <algorithm> 
#include <stdexcept>

// Create a new item listing interactively
void ItemDataController::createItemListing() const {
    std::string name = InputValidator::validateString("Enter item name: ");
    Category::displayCategories();
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
// Search items by category
std::vector<Item> ItemDataController::searchItemsByCategory(const std::string& category) const {
    auto items = ItemDAO.getAllItems();
    std::vector<Item> result;

    for (const auto& item : items) {
        if (item.getCategory() == category) {
            result.push_back(item);
        }
    }

    if (result.empty()) {
        std::cout << "No items found in category: " << category << "\n";
    }

    return result;
}

// Search items by keyword
std::vector<Item> ItemDataController::searchItemsByKeyword(const std::string& keyword) const {
    auto items = ItemDAO.getAllItems();
    std::vector<Item> result;

    for (const auto& item : items) {
        if (item.getName().find(keyword) != std::string::npos || 
            item.getDescription().find(keyword) != std::string::npos) {
            result.push_back(item);
        }
    }

    if (result.empty()) {
        std::cout << "No items found with keyword: " << keyword << "\n";
    }

    return result;
}

// Sort items by criteria
std::vector<Item> ItemDataController::sortItemsBy(const std::string& criteria) const {
    auto items = ItemDAO.getAllItems();

    if (criteria == "endTime") {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getEndTime() < b.getEndTime();
        });
    } else if (criteria == "startingBid") {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getStartingBid() < b.getStartingBid();
        });
    } else if (criteria == "currentBid") {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getCurrentBid() < b.getCurrentBid();
        });
    } else {
        std::cerr << "Invalid sorting criteria.\n";
    }

    return items;
}

bool ItemDataController::editItem(const std::string& itemId, const std::string& newDescription, double newStartingBid) {
    auto itemOpt = ItemDAO.findItemById(itemId);
    if (!itemOpt) {
        std::cerr << "Error: Item not found.\n";
        return false;
    }

    auto item = itemOpt.value();
    item.setStartingBid(newStartingBid);
    item.setBidIncrement(newStartingBid / 10); // Adjust increment based on new starting bid
    item.setDescription(newDescription);
    ItemDAO.updateItem(item);
    return true;
}

bool ItemDataController::deleteItem(const std::string& itemId) {
    if (ItemDAO.deleteItemById(itemId)) {
        std::cout << "Item deleted successfully.\n";
        return true;
    }
    std::cerr << "Error: Item not found.\n";
    return false;
}
