
#ifndef ITEMDATACONTROLLER_H
#define ITEMDATACONTROLLER_H

#include "../dao/ItemListingHandler.h"
#include "../class/Item.h"
#include <string>
#include <chrono>

class ItemDataController {
public:
    // Create a new item listing (interactive or direct)
    void createItemListing() const; // Interactive
   void createItemListing(const std::string& name, const std::string& category, const std::string& description, 
                       double startingBid, double bidIncrement, std::chrono::system_clock::time_point endTime) const;

    // View all item listings
    void viewListings() const;

    // Save item listings to file
    void saveListingsToFile(const std::string& filePath) const;

    // Load item listings from file
    void loadListingsFromFile(const std::string& filePath);

private:
    mutable ItemListingHandler ItemDAO; // Manages item data storage and retrieval
};

#endif // ITEMDATACONTROLLER_H
