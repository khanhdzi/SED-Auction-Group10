#include "../../include/dao/ItemListingHandler.h"
#include <fstream>
#include <iostream>
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
    std::filesystem::create_directories("data");
    std::ofstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for saving items.\n";
        return;
    }

    size_t size = items.size();
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
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for loading items.\n";
        return;
    }

    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    items.clear();
    for (size_t i = 0; i < size; ++i) {
        Item item("", "", "", 0.0, 0.0, std::chrono::system_clock::now(), 0);
        item.deserialize(file);
        items.push_back(item);
    }

    file.close();
    std::cout << "Items loaded successfully from " << filePath << ".\n";
}
