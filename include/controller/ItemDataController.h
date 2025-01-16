#ifndef ITEMDATACONTROLLER_H
#define ITEMDATACONTROLLER_H

#include "../dao/ItemListingHandler.h"
#include "../class/Item.h"
#include <string>
#include <vector>
#include <chrono>

class ItemDataController {
public:
    // Create a new item listing (interactive or direct)
    void createItemListing() const; // Interactive
    void createItemListing(const std::string& name, const std::string& category, 
                           const std::string& description, double startingBid, 
                           double bidIncrement, std::chrono::system_clock::time_point endTime) const;

    // View all item listings
    void viewListings() const;

    // Save and load listings
    void saveListingsToFile(const std::string& filePath) const;
    void loadListingsFromFile(const std::string& filePath);

    // sort Item 
    std::vector<Item> searchItemsByCategory(const std::string& category) const;
    std::vector<Item> searchItemsByKeyword(const std::string& keyword) const;
    std::vector<Item> sortItemsBy(const std::string& criteria) const;

     // Edit an item listing
    bool editItem(const std::string& itemId, const std::string& newDescription, double newStartingBid);

    // Delete an item listing
    bool deleteItem(const std::string& itemId);


private:
    mutable ItemListingHandler ItemDAO; // Manages item data storage and retrieval
};

#endif // ITEMDATACONTROLLER_H
