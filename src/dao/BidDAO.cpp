#include "../../include/dao/BidDAO.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

const std::string BidDAO::FILE_PATH = "data/bids.dat";

// Save a bid to the file
bool BidDAO::saveBid(const Bid& bid) {
    std::ofstream file(FILE_PATH, std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving bid.\n";
        return false;
    }

    bid.serialize(file);
    file.close();
    return true;
}

// Retrieve all bids from the file
std::vector<Bid> BidDAO::getAllBids() const {
    std::vector<Bid> bids;
    std::ifstream file(FILE_PATH, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading bids.\n";
        return bids;
    }

    while (file.peek() != EOF) {
        Bid bid;
        bid.deserialize(file);
        bids.push_back(bid);
    }

    file.close();
    return bids;
}

// Find bids by item ID
std::vector<Bid> BidDAO::findBidsByItemId(const std::string& itemId) const {
    auto allBids = getAllBids();
    std::vector<Bid> result;

    std::copy_if(allBids.begin(), allBids.end(), std::back_inserter(result), [&](const Bid& bid) {
        return bid.getItemId() == itemId;
    });

    return result;
}

// Get active bids placed by a user
std::vector<Bid> BidDAO::getActiveBidsByUser(const std::string& bidderId) const {
    auto allBids = getAllBids();
    std::vector<Bid> result;

    std::copy_if(allBids.begin(), allBids.end(), std::back_inserter(result), [&](const Bid& bid) {
        return bid.getBidderId() == bidderId;
    });

    return result;
}
bool BidDAO::placeBid(const Bid& bid) {
    auto highestBid = findBidsByItemId(bid.getItemId());
    if (!highestBid.empty() && bid.getBidAmount() <= highestBid.back().getBidAmount()) {
        std::cerr << "Error: Bid amount must be higher than the current highest bid.\n";
        return false;
    }
    return saveBid(bid);
}

std::optional<Bid> BidDAO::getHighestBid(const std::string& itemId) const {
    auto bids = findBidsByItemId(itemId);
    if (bids.empty()) {
        return std::nullopt;
    }

    auto highestBid = *std::max_element(bids.begin(), bids.end(), [](const Bid& a, const Bid& b) {
        return a.getBidAmount() < b.getBidAmount();
    });

    return highestBid;
}