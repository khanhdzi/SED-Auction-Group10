#include "../../include/class/Bid.h"
#include <ctime>

Bid::Bid(const std::string& itemId, const std::string& bidderId, double amount)
    : itemId(itemId), bidderId(bidderId), bidAmount(amount), automaticBidLimit(0) {
    bidTime = time(nullptr);
}

Bid::Bid(const std::string& itemId, const std::string& bidderId, double amount, double bidLimit)
    : itemId(itemId), bidderId(bidderId), bidAmount(amount), automaticBidLimit(bidLimit) {
    bidTime = time(nullptr);
}

// Getters
std::string Bid::getItemId() const {
    return itemId;
}

std::string Bid::getBidderId() const {
    return bidderId;
}

double Bid::getBidAmount() const {
    return bidAmount;
}

double Bid::getAutomaticBidLimit() const {
    return automaticBidLimit;
}

std::time_t Bid::getBidTime() const {
    return bidTime;
}

// Setters
void Bid::setAutomaticBidLimit(double bidLimit) {
    automaticBidLimit = bidLimit;
}
