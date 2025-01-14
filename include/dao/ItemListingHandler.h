#ifndef ITEMLISTINGHANDLER_H
#define ITEMLISTINGHANDLER_H

#include "../class/Item.h"
#include <vector>

class ItemListingHandler {
public:
    // Add a new listing
    void addListing(Item item);

    // Remove a listing
    bool removeListing(int itemId);

    // Edit a listing (only before bids have started)
    bool editListing(int itemId, double newStartingBid, double newBidIncrement);

    // View all listings
    void viewAllListings() const;

private:
    std::vector<Item> listings;
};

#endif // ITEMLISTINGHANDLER_H