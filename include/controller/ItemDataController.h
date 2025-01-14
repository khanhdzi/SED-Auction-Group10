


#ifndef ITEMDATACONTROLLER_H
#define ITEMDATACONTROLLER_H

#include "../class/Item.h"
#include "../dao/ItemListingHandler.h"
#include <vector>
#include <string>



class ItemDataController {
public:
    // Create a new item listing
    void createItemListing(std::string name, std::string category, std::string description, 
                           double startingBid, double bidIncrement, std::chrono::system_clock::time_point endTime,
                           int minBuyerRating);

    // View all item listings
    void viewListings() const;

private:
    ItemListingHandler listingHandler;
};

#endif // ITEMDATACONTROLLER_H
