#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <ctime>

// Represents an individual item
class ItemListing {
public:
    int id;                    // Unique ID for the item
    std::string name;          // Name of the item
    std::string category;      // Category of the item
    std::string description;   // A brief description of the item
    int startingBid;           // Starting bid price
    int bidIncrement;          // Minimum increment for bids
    time_t endTime;            // Auction end time
    int minBuyerRating;        // Minimum buyer rating required to bid

    // Constructor to initialize an item
    ItemListing(int itemId, const std::string& itemName, const std::string& cat, const std::string& desc, int startBid, int increment, time_t end, int minRating);

    // Default constructor for reading from files
    ItemListing();
};

#endif // ITEM_H
