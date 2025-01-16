#ifndef ITEMLISTINGHANDLER_H
#define ITEMLISTINGHANDLER_H

#include "../class/Item.h"
#include <vector>
#include <string>
#include <optional>

class ItemListingHandler {
public:
    void addItem(const Item& item);
    bool removeItem(int index);
    std::vector<Item> getAllItems() const;
    std::optional<Item> findItemById(const std::string& itemId) const;
    // Save and load methods
    void saveItems() const; // Save to default file path
    void saveItems(const std::string& filePath) const; // Save to specified file path
    void loadItems(); // Load from default file path
    void loadItems(const std::string& filePath); // Load from specified file path

private:
    std::vector<Item> items;
    static const std::string defaultFilePath;
};

#endif // ITEMLISTINGHANDLER_H
