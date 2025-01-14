#include "../../include/class/Item.h"

Item::Item(const std::string& itemId, const std::string& name, double price, const std::string& category)
    : itemId(itemId), name(name), price(price), category(category) {}

std::string Item::getItemId() const {
    return itemId;
}

std::string Item::getName() const {
    return name;
}

double Item::getPrice() const {
    return price;
}

std::string Item::getCategory() const {
    return category;
}

double Item::getHighestBid() const {
    return highestBid;  // Return highest bid
}

std::string Item::getHighestBidder() const {
    return highestBidder;  // Return highest bidder
}

std::string Item::getEndDate() const {
    return endDate;  // Return end date of the auction
}

int Item::getCreditPoints() const {
    return creditPoints;  // Return the credit points of the item
}
