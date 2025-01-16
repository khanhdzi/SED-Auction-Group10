#ifndef BID_CONTROLLER_H
#define BID_CONTROLLER_H

#include "../dao/BidDAO.h"
#include "../dao/ItemListingHandler.h"
#include "../class/Authenticator.h"
#include <string>
#include <vector>

class BidController {
public:
    // Place a bid
    void placeBid(const std::string& itemId, double amount, double bidLimit = 0.0);

    // View all bids for a specific item
    void viewBidsForItem(const std::string& itemId) const;

    // View active bids placed by the logged-in user
    void viewUserBids() const;

    // Automatically handle bidding up to the bid limit
    void handleAutomaticBidding(const std::string& itemId);

private:
    BidDAO bidDAO;               // Handles bid storage and retrieval
    ItemListingHandler itemDAO;  // Handles item storage and retrieval

    // Helper to resolve automatic bid limit conflicts
    bool resolveAutomaticBidLimitConflict(const std::string& itemId, double bidLimit) const;

    // Display bid details
    void displayBids(const std::vector<Bid>& bids) const;
};

#endif // BID_CONTROLLER_H
