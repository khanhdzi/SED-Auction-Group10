#include "../../include/dao/ItemListingHandler.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <ctime>

const std::string ItemListingHandler::defaultFilePath = "data/items.dat";

ItemListingHandler::ItemListingHandler() {
    loadItems(defaultFilePath);
}

void ItemListingHandler::addItem(const Item& item) {
    items.push_back(item);
}

bool ItemListingHandler::removeItemById(const std::string& itemId) {
    auto it = std::remove_if(items.begin(), items.end(),
        [&itemId](const Item& item) { return item.getItemID() == itemId; });
    if (it != items.end()) {
        items.erase(it, items.end());
        return true;
    }
    return false;
}

std::optional<Item> ItemListingHandler::findItemById(const std::string& itemId) const {
    auto it = std::find_if(items.begin(), items.end(),
        [&itemId](const Item& item) { return item.getItemID() == itemId; });
    if (it != items.end()) {
        return *it;
    }
    return std::nullopt;
}

bool ItemListingHandler::editItem(const std::string& itemId, const std::string& newDescription, double newStartingBid) {
    for (auto& item : items) {
        if (item.getItemID() == itemId) {
            item.setDescription(newDescription);
            item.setStartingBid(newStartingBid);
            return true;
        }
    }
    return false;
}

std::vector<Item> ItemListingHandler::getAllItems() const {
    return items;
}

std::vector<Item> ItemListingHandler::searchItemsByCategory(const std::string& category) const {
    std::vector<Item> result;
    std::copy_if(items.begin(), items.end(), std::back_inserter(result),
        [&category](const Item& item) { return item.getCategory() == category; });
    return result;
}

std::vector<Item> ItemListingHandler::searchItemsByKeyword(const std::string& keyword) const {
    std::vector<Item> result;
    std::copy_if(items.begin(), items.end(), std::back_inserter(result),
        [&keyword](const Item& item) {
            return item.getName().find(keyword) != std::string::npos ||
                   item.getDescription().find(keyword) != std::string::npos;
        });
    return result;
}

std::vector<Item> ItemListingHandler::sortItemsBy(const std::string& criteria) const {
    auto sortedItems = items;
    if (criteria == "endTime") {
        std::sort(sortedItems.begin(), sortedItems.end(),
                  [](const Item& a, const Item& b) { return a.getEndTime() < b.getEndTime(); });
    } else if (criteria == "startingBid") {
        std::sort(sortedItems.begin(), sortedItems.end(),
                  [](const Item& a, const Item& b) { return a.getStartingBid() < b.getStartingBid(); });
    } else if (criteria == "currentBid") {
        std::sort(sortedItems.begin(), sortedItems.end(),
                  [](const Item& a, const Item& b) { return a.getCurrentBid() < b.getCurrentBid(); });
    }
    return sortedItems;
}

void ItemListingHandler::saveItems(const std::string& filePath) const {
    std::cout << "Debug: Saving items to file: " << filePath << "\n";

    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << " for saving items.\n";
        return;
    }

    size_t size = items.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& item : items) {
        std::cout << "Debug: Writing item to file - ID: " << item.getItemID()
                  << ", Status: " << item.getStatus() << "\n";
        item.serialize(file);
    }

    file.close();
    std::cout << "Debug: All items saved to file successfully.\n";
}



void ItemListingHandler::loadItems(const std::string& filePath) {
    std::cout << "Debug: Loading items from file: " << filePath << "\n";

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << " for loading items.\n";
        return;
    }

    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    items.clear();
    for (size_t i = 0; i < size; ++i) {
        Item item;
        item.deserialize(file);
        items.push_back(item);

        std::cout << "Debug: Loaded item - ID: " << item.getItemID()
                  << ", Status: " << item.getStatus() << "\n";
    }

    file.close();
    std::cout << "Debug: All items loaded successfully.\n";
}



/* void ItemListingHandler::displayItems(const std::vector<Item>& items) const {
    for (const auto& item : items) {
        if (item.getStatus() != "active") {
            continue; // Skip closed items
        }

        auto endTimeT = std::chrono::system_clock::to_time_t(item.getEndTime());
        std::string endTimeStr = std::ctime(&endTimeT);
        endTimeStr.pop_back();

        std::cout << "ID: " << item.getItemID()
                  << ", Name: " << item.getName()
                  << ", Category: " << item.getCategory()
                  << ", Seller: " << item.getSellerID()
                  << ", Current Bidder: " << (item.getCurrentBidder().empty() ? "No bidders" : item.getCurrentBidder())
                  << ", Starting Bid: " << item.getStartingBid()
                  << ", Current Bid: " << item.getCurrentBid()
                  << ", Bid Increment: " << item.getBidIncrement()
                  << ", Minimum Buyer Rating: " << item.getMinBuyerRating()
                  << ", End Time: " << endTimeStr
                  << ", Status: " << item.getStatus()
                  << "\n";
    }
}
 */

void ItemListingHandler::displayItems(const std::vector<Item>& items) const {
    for (const auto& item : items) {
        if (item.getStatus() != "active") {
            std::cout << "Debug: Skipping closed item - ID: " << item.getItemID() << "\n";
            continue;
        }

        auto endTimeT = std::chrono::system_clock::to_time_t(item.getEndTime());
        std::string endTimeStr = std::ctime(&endTimeT);
        endTimeStr.pop_back();

        std::cout << "ID: " << item.getItemID()
                  << ", Name: " << item.getName()
                  << ", Status: " << item.getStatus()
                  << "\n";
    }
}


bool ItemListingHandler::updateItem(const Item& updatedItem) {
    std::cout << "Debug: Updating item with ID: " << updatedItem.getItemID() 
              << ". Current Bidder: " << updatedItem.getCurrentBidder() 
              << ", Current Bid: " << updatedItem.getCurrentBid() << "\n";

    for (auto& item : items) {
        if (item.getItemID() == updatedItem.getItemID()) {
            item = updatedItem; // Replace the item in the vector
            saveItems(defaultFilePath); // Save updated vector to the file
            std::cout << "Debug: Item updated successfully in memory and file.\n";
            return true;
        }
    }

    std::cerr << "Error: Item with ID " << updatedItem.getItemID() << " not found for update.\n";
    return false;
}




