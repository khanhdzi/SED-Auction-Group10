#include "../../include/dao/ItemListingHandler.h"
#include <iostream>

void ItemListingHandler::addListing(Item item) {
    listings.push_back(item);
}

bool ItemListingHandler::removeListing(int itemId) {
    if (itemId >= 0 && itemId < listings.size()) {
        listings.erase(listings.begin() + itemId);
        return true;
    }
    return false;
}

bool ItemListingHandler::editListing(int itemId, double newStartingBid, double newBidIncrement) {
    if (itemId >= 0 && itemId < listings.size()) {
        Item& item = listings[itemId];
        // You can only edit listings if no bids have been placed yet
        // Implement checking for bids here if necessary
        item.setStartingBid(newStartingBid);
        item.setBidIncrement(newBidIncrement);
        return true;
    }
    return false;
}

void ItemListingHandler::viewAllListings() const {
    for (const auto& item : listings) {
        std::cout << "Item: " << item.getName() << ", Category: " << item.getCategory() << ", Starting Bid: "
                  << item.getStartingBid() << ", Bid Increment: " << item.getBidIncrement() << "\n";
    }
}
