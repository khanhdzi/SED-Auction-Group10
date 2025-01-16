#ifndef BID_DAO_H
#define BID_DAO_H

#include "../class/Bid.h"
#include <vector>
#include <string>
#include <optional>

class BidDAO {
private:
    static const std::string FILE_PATH;

public:
    bool saveBid(const Bid& bid); // Save a bid
    std::vector<Bid> getAllBids() const; // Retrieve all bids
    std::vector<Bid> findBidsByItemId(const std::string& itemId) const; // Find bids by item ID
    std::vector<Bid> getActiveBidsByUser(const std::string& bidderId) const; // Get active bids by a user

    // Get the highest bid for an item
    std::optional<Bid> getHighestBid(const std::string& itemId) const;

    bool placeBid(const Bid& bid); // Place a bid
};

#endif // BID_DAO_H
