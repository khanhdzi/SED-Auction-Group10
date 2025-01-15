#include "../../include/class/Item.h"

Item::Item(const std::string& itemId, const std::string& name, double price, const std::string& category)
    : itemId(itemId), name(name), price(price), category(category) {}

// Setters
void Item::setHighestBid(double bid) {
    highestBid = bid;
}

void Item::setHighestBidder(const std::string& bidder) {
    highestBidder = bidder;
}

void Item::setEndDate(const std::string& endDate) {
    this->endDate = endDate;
}

void Item::setOwnerId(const std::string& ownerId) {  // Set ownerId
    this->ownerId = ownerId;
}

// Getters
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
    return highestBid;
}

std::string Item::getHighestBidder() const {
    return highestBidder;
}

std::string Item::getEndDate() const {
    return endDate;
}

std::string Item::getOwnerId() const {  // Return ownerId
    return ownerId;
}

int Item::getCreditPoints() const {
    return creditPoints;
}
