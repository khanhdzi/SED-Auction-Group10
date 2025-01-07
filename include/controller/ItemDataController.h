#ifndef ITEM_DATA_CONTROLLER_H
#define ITEM_DATA_CONTROLLER_H

#include "Item.h"
#include <vector>
#include <string>

// Handles data persistence for item listings
class ItemDataController {
private:
    const std::string filename; // File to store item data

public:
    // Constructor with filename
    explicit ItemDataController(const std::string& file);

    // Save all items to the file
    void saveToFile(const std::vector<ItemListing>& items);

    // Load all items from the file
    std::vector<ItemListing> loadFromFile();
};

#endif // ITEM_DATA_CONTROLLER_H
