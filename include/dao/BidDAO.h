#ifndef BID_DAO_H
#define BID_DAO_H

#include "../class/Bid.h"
#include <vector>
#include <optional>

class BidDAO {
private:
    static const std::string FILE_PATH; // File path for storing bids

public:
    bool saveBid(const Bid& bid);               // Save a bid to the file
    std::vector<Bid> getAllBids();             // Retrieve all bids from the file
    std::vector<Bid> findBidsByItemId(const std::string& itemId); // Find bids by item ID
    static const std::string& getFilePath() { return FILE_PATH; } // Access file path
    // Method to place a bid
    bool placeBid(const Bid& bid);

    // Method to get active bids by a user
    std::vector<Bid> getActiveBidsByUser(const std::string& bidderId);
};

#endif
