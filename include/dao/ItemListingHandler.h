#ifndef ITEMLISTINGHANDLER_H
#define ITEMLISTINGHANDLER_H

#include "../class/Item.h"
#include <vector>
#include <string>
#include <optional>

class ItemListingHandler {
public:
    // Add a new item
    void addItem(const Item& item);

    // Remove an item by index
    bool removeItem(int index);

    // Retrieve all items
    std::vector<Item> getAllItems() const;

    // Find an item by its ID
    std::optional<Item> findItemById(const std::string& itemId) const;

    // Update an existing item
    bool updateItem(const Item& updatedItem);

    // Delete an item by ID
    bool deleteItemById(const std::string& itemId);

    // Save and load methods
    void saveItems() const; // Save to default file path
    void saveItems(const std::string& filePath) const; // Save to specified file path
    void loadItems(); // Load from default file path
    void loadItems(const std::string& filePath); // Load from specified file path

private:
    std::vector<Item> items; // Stores all item listings
    static const std::string defaultFilePath; // Default file path for items
};

#endif // ITEMLISTINGHANDLER_H
