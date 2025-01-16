#include "../../include/controller/BidController.h"
#include <iostream>
#include <iomanip>

// Helper: Display a list of bids
void BidController::displayBids(const std::vector<Bid>& bids) const {
    if (bids.empty()) {
        std::cout << "No bids available.\n";
        return;
    }

    std::cout << std::left << std::setw(15) << "Item ID"
              << std::setw(15) << "Bidder"
              << std::setw(10) << "Amount"
              << std::setw(25) << "Bid Time\n";
    std::cout << std::string(65, '-') << "\n";

    for (const auto& bid : bids) {
        std::time_t bidTime = std::chrono::system_clock::to_time_t(bid.getBidTime());
        std::cout << std::left << std::setw(15) << bid.getItemId()
                  << std::setw(15) << bid.getBidderId()
                  << "$" << std::setw(9) << bid.getBidAmount()
                  << std::ctime(&bidTime);
    }
}

// Place a bid
void BidController::placeBid(const std::string& itemId, double amount, double bidLimit) {
    if (!Authenticator::isLoggedIn()) {
        std::cerr << "You must be logged in to place a bid.\n";
        return;
    }

    User* user = Authenticator::getLoggedUser();

    // Fetch item details
    auto itemOpt = itemDAO.findItemById(itemId);
    if (!itemOpt) {
        std::cerr << "Error: Item not found.\n";
        return;
    }


    auto item = itemOpt.value();

    // Validate bid amount
    if (amount < item.getCurrentBid() + item.getBidIncrement()) {
        std::cerr << "Error: Your bid must be at least " 
                  << item.getCurrentBid() + item.getBidIncrement() << " CP.\n";
        return;
    }

    // Resolve automatic bid limit conflict
    if (bidLimit > 0 && !resolveAutomaticBidLimitConflict(itemId, bidLimit)) {
        std::cerr << "Error: Automatic bid limit conflict. Please set a higher limit.\n";
        return;
    }

    // Save bid
    Bid newBid(itemId, user->getUsername(), amount, bidLimit);
    if (bidDAO.placeBid(newBid)) {
        std::cout << "Bid placed successfully.\n";

        // Handle automatic bidding if a limit is set
        if (bidLimit > 0) {
            handleAutomaticBidding(itemId);
        }
    } else {
        std::cerr << "Failed to place bid.\n";
    }
}

// View all bids for an item
void BidController::viewBidsForItem(const std::string& itemId) const {
    auto bids = bidDAO.findBidsByItemId(itemId);
    std::cout << "Bids for Item ID: " << itemId << "\n";
    displayBids(bids);
}

// View user's active bids
void BidController::viewUserBids() const {
    if (!Authenticator::isLoggedIn()) {
        std::cerr << "You must be logged in to view your bids.\n";
        return;
    }

    User* user = Authenticator::getLoggedUser();
    auto bids = bidDAO.getActiveBidsByUser(user->getUsername());
    std::cout << "Active Bids for User: " << user->getUsername() << "\n";
    displayBids(bids);
}

// Automatically handle bidding up to the bid limit
void BidController::handleAutomaticBidding(const std::string& itemId) {
    auto highestBid = bidDAO.getHighestBid(itemId);
    if (!highestBid) return;

    auto itemOpt = itemDAO.findItemById(itemId);
    if (!itemOpt) return;

    const auto& item = itemOpt.value();
    auto bids = bidDAO.findBidsByItemId(itemId);

    for (const auto& bid : bids) {
        if (bid.getAutomaticBidLimit() > highestBid->getBidAmount() &&
            bid.getAutomaticBidLimit() >= highestBid->getBidAmount() + item.getBidIncrement()) {
            double newBidAmount = std::min(bid.getAutomaticBidLimit(), 
                                           highestBid->getBidAmount() + item.getBidIncrement());
            placeBid(itemId, newBidAmount);
        }
    }
}

// Resolve automatic bid limit conflicts
bool BidController::resolveAutomaticBidLimitConflict(const std::string& itemId, double bidLimit) const {
    auto bids = bidDAO.findBidsByItemId(itemId);
    for (const auto& bid : bids) {
        if (bid.getAutomaticBidLimit() == bidLimit) {
            return false; // Conflict found
        }
    }
    return true; // No conflict
}
