#ifndef ITEMDATACONTROLLER_H
#define ITEMDATACONTROLLER_H

#include "../dao/ItemListingHandler.h" // Ensure this is included
#include <string>
#include <chrono>

class ItemDataController {
public:
    void createItem();
    void editItem();
    void deleteItem();
    void viewAllItems() const;
    void searchItemsByCategory() const;
    void searchItemsByKeyword() const;
    void sortItemsBy() const;
    void saveListingsToFile() const;
    void loadListingsFromFile();

    // Check if the item ID exists
    bool isItemIDExist(const std::string& itemID) const;
private:
    ItemListingHandler itemDAO; // Handles item storage and operations
    const std::string defaultFilePath = "data/items.dat";
};

#endif // ITEMDATACONTROLLER_H
