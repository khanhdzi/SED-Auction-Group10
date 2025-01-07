// src/controller/BidController.cpp
#include "../../include/controller/BidController.h"

bool BidController::placeBid(const std::string& itemId, const std::string& bidderId, double amount) {
    if (!validateBid(itemId, bidderId, amount)) {
        return false;
    }
    
    Bid newBid(itemId, bidderId, amount);
    return bidDAO.placeBid(newBid);
}