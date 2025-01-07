// src/class/Bid.cpp
#include "../../include/class/Bid.h"

Bid::Bid(const std::string& itemId, const std::string& bidderId, double amount)
    : itemId(itemId), bidderId(bidderId), bidAmount(amount), automaticBidLimit(0) {
    bidTime = time(nullptr);
}

Bid::Bid(const std::string& itemId, const std::string& bidderId, double amount, double bidLimit)
    : itemId(itemId), bidderId(bidderId), bidAmount(amount), automaticBidLimit(bidLimit) {
    bidTime = time(nullptr);
}

// Implement getters and setters...