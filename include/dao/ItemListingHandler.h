#ifndef ITEMLISTINGHANDLER_H
#define ITEMLISTINGHANDLER_H

#include "../class/Item.h"
#include <vector>
#include <string>
#include <optional>

class ItemListingHandler {
public:
    ItemListingHandler();
    void addItem(const Item& item);
    bool removeItemById(const std::string& itemId);
    std::optional<Item> findItemById(const std::string& itemId) const;
    bool editItem(const std::string& itemId, const std::string& newDescription, double newStartingBid);
    std::vector<Item> getAllItems() const;
    std::vector<Item> searchItemsByCategory(const std::string& category) const;
    std::vector<Item> searchItemsByKeyword(const std::string& keyword) const;
    std::vector<Item> sortItemsBy(const std::string& criteria) const;
    void saveItems(const std::string& filePath) const;
    void loadItems(const std::string& filePath);
    void displayItems(const std::vector<Item>& items) const;

private:
    std::vector<Item> items;
    static const std::string defaultFilePath;
};

#endif // ITEMLISTINGHANDLER_H
