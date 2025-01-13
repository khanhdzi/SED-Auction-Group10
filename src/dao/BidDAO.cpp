#include "../../include/dao/BidDAO.h"
#include <fstream>
#include <iostream>

const std::string BidDAO::FILE_PATH = "data/bids.dat";

// Save a bid to the binary file
bool BidDAO::saveBid(const Bid& bid) {
    std::ofstream file(FILE_PATH, std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving bid.\n";
        return false;
    }
    bid.serialize(file);
    file.close();
    return true;
}

bool BidDAO::placeBid(const Bid& bid) {
    // Insert the bid into the database or collection logic here
    // If successful:
    return true;
    // If something goes wrong:
    return false;
}

std::vector<Bid> BidDAO::getActiveBidsByUser(const std::string& bidderId) {
    std::vector<Bid> activeBids;
    // Logic to fetch active bids for the user
    // Example: Iterate through a list of all bids and add the user's active bids
    return activeBids;
}


// Get all bids from the binary file
std::vector<Bid> BidDAO::getAllBids() {
    std::vector<Bid> bids;
    std::ifstream file(FILE_PATH, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading bids.\n";
        return bids;
    }

    // Read bids from the file until the end
    while (file.peek() != EOF) {
        Bid bid;
        bid.deserialize(file);
        bids.push_back(bid);
    }

    file.close();
    return bids;
}

// Find bids by item ID
std::vector<Bid> BidDAO::findBidsByItemId(const std::string& itemId) {
    std::vector<Bid> allBids = getAllBids();
    std::vector<Bid> matchingBids;

    for (const auto& bid : allBids) {
        if (bid.getItemId() == itemId) {
            matchingBids.push_back(bid);
        }
    }

    return matchingBids;
}
