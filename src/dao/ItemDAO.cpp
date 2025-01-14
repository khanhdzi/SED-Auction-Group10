// src/class/ItemDAO.cpp

#include "../../include/DAO/ItemDAO.h"
#include <iostream>

ItemDAO::ItemDAO() {
    // You can initialize some data or load data from a database/file if needed
}

// Fetches all items (this can be from an in-memory list or a database)
std::vector<Item> ItemDAO::getAllItems() const {
    std::vector<Item> items;
    // Example of static items, but you'd likely query a database or file here
    items.push_back(Item("1", "Item 1", 100.0, "Category 1"));
    items.push_back(Item("2", "Item 2", 150.0, "Category 2"));
    return items;
}

// Find an item by its ID
std::optional<Item> ItemDAO::findItemById(const std::string& itemId) const {
    std::vector<Item> items = getAllItems();
    for (const auto& item : items) {
        if (item.getItemId() == itemId) {
            return item;
        }
    }
    return std::nullopt;  // Item not found
}
