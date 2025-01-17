#include "../../include/dao/ItemListingHandler.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>

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
    std::filesystem::create_directories(std::filesystem::path(filePath).parent_path());
    std::ofstream file(filePath, std::ios::binary);
    size_t size = items.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& item : items) {
        item.serialize(file);
    }
}

void ItemListingHandler::loadItems(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << " for loading items.\n";
        return;
    }

    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    if (file.fail() || size == 0) {
        std::cerr << "Error: File " << filePath << " is empty or invalid.\n";
        return;
    }

    items.clear();
    for (size_t i = 0; i < size; ++i) {
        // Updated constructor call to include sellerID
        Item item("", "", "", 0.0, 0.0, std::chrono::system_clock::now(), 0, "");
        item.deserialize(file);
        items.push_back(item);
    }

    file.close();
    std::cout << "Items loaded successfully from " << filePath << ".\n";
}


void ItemListingHandler::displayItems(const std::vector<Item>& items) const {
    for (const auto& item : items) {
        std::cout << "ID: " << item.getItemID() 
                  << ", Name: " << item.getName() 
                  << ", Category: " << item.getCategory() 
                  << ", Seller: " << item.getSellerID() 
                  << ", Current Bidder: " << item.getCurrentBidder() 
                  << ", Starting Bid: " << item.getStartingBid()
                  << ", Current Bid: " << item.getCurrentBid()  
                  << "\n";
    }
}

bool ItemListingHandler::updateItem(const Item& updatedItem) {
    for (auto& item : items) {
        if (item.getItemID() == updatedItem.getItemID()) {
            item = updatedItem;

            // Save all items to the file to reflect the change
            saveItems(defaultFilePath);

            return true;
        }
    }
    return false; // Return false if the item was not found
}

