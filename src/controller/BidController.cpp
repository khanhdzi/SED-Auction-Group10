#include "../../include/controller/BidController.h"
#include <iostream>

bool BidController::validateBid(const std::string& itemId, const std::string& bidderId, double amount) {
    // Example validation logic
    if (itemId.empty() || bidderId.empty() || amount <= 0) {
        std::cerr << "Invalid bid details.\n";
        return false;
    }
    return true;
}

bool BidController::placeBid(const std::string& itemId, const std::string& bidderId, double amount) {
    if (!validateBid(itemId, bidderId, amount)) {
        return false;
    }

    Bid newBid(itemId, bidderId, amount);
    return bidDAO.placeBid(newBid);
}
