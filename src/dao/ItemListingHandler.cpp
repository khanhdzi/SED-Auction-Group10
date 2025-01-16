#include "../../include/dao/ItemListingHandler.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

const std::string ItemListingHandler::defaultFilePath = "data/items.dat";

// Add a new item
void ItemListingHandler::addItem(const Item& item) {
    items.push_back(item);
}

// Remove an item by index
bool ItemListingHandler::removeItem(int index) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        std::cerr << "Error: Invalid index.\n";
        return false;
    }
    items.erase(items.begin() + index);
    return true;
}

// Retrieve all items
std::vector<Item> ItemListingHandler::getAllItems() const {
    return items;
}

// Save items to the default file path
void ItemListingHandler::saveItems() const {
    saveItems(defaultFilePath);
}

// Save items to a specified file path
void ItemListingHandler::saveItems(const std::string& filePath) const {
    // Ensure directory exists
    std::filesystem::create_directories("data");

    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for saving items.\n";
        return;
    }

    size_t size = items.size();
    std::cout << "Saving " << size << " items to file.\n";

    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& item : items) {
        item.serialize(file);
    }

    file.close();
    std::cout << "Items saved successfully to " << filePath << ".\n";
}



// Load items from the default file path
void ItemListingHandler::loadItems() {
    loadItems(defaultFilePath);
}

// Load items from a specified file path

void ItemListingHandler::loadItems(const std::string& filePath) {
    // Debug message to show the file path being used
    std::cout << "Attempting to load items from: " << filePath << "\n";

    // Check if the file exists
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "Error: File not found at " << filePath << ".\n";
        return;
    }

    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for loading items.\n";
        return;
    }

    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    // Check if the file is empty or invalid
    if (file.fail() || size == 0) {
        std::cerr << "Error: File is empty or contains invalid data.\n";
        file.close();
        return;
    }

    items.clear();
    for (size_t i = 0; i < size; ++i) {
        try {
            Item item("", "", "", 0.0, 0.0, std::chrono::system_clock::now(), 0);
            item.deserialize(file);

            // Validate the deserialized item (optional)
            if (item.getName().empty() || item.getCategory().empty()) {
                std::cerr << "Warning: Skipping invalid item at index " << i << ".\n";
                continue;
            }

            items.push_back(item);
        } catch (const std::exception& e) {
            std::cerr << "Error: Failed to deserialize item at index " << i << ". Exception: " << e.what() << "\n";
        }
    }

    file.close();
    std::cout << "Items loaded successfully from " << filePath << ".\n";
}


bool ItemListingHandler::updateItem(const Item& updatedItem) {
    for (auto& item : items) {
        if (item.getName() == updatedItem.getName()) { // Assuming item name is the ID
            item = updatedItem;
            return true;
        }
    }
    return false;
}

// Delete an item by ID
bool ItemListingHandler::deleteItemById(const std::string& itemId) {
    auto it = std::remove_if(items.begin(), items.end(), [&](const Item& item) {
        return item.getName() == itemId; // Assuming item name is the ID
    });

    if (it != items.end()) {
        items.erase(it, items.end());
        return true;
    }
    return false;
}