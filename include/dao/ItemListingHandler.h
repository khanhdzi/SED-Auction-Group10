#ifndef ITEMLISTINGHANDLER_H
#define ITEMLISTINGHANDLER_H

#include "../class/Item.h"
#include <vector>
#include <string>

class ItemListingHandler {
public:
    // Add a new item to the listing
    void addItem(const Item& item);

    // Remove an item by index
    bool removeItem(int index);

    // Retrieve all items
    std::vector<Item> getAllItems() const;

    // Save items to the default file
    void saveItems() const;

    // Load items from the default file
    void loadItems();

private:
    std::vector<Item> items;
    static const std::string defaultFilePath; // Default file path for storing items
};

#endif // ITEMLISTINGHANDLER_H