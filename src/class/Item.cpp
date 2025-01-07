#include "Item.h"

// Constructor with parameters
ItemListing::ItemListing(int itemId, const std::string& itemName, const std::string& cat, const std::string& desc, int startBid, int increment, time_t end, int minRating)
    : id(itemId), name(itemName), category(cat), description(desc), startingBid(startBid), bidIncrement(increment), endTime(end), minBuyerRating(minRating) {}

// Default constructor
ItemListing::ItemListing() {}
