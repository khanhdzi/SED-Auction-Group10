#include "../../include/dao/BidDAO.h"
#include <fstream>
#include <iostream>

bool BidDAO::placeBid(const Bid& bid) {
    // Example of saving bid details to a file
    std::ofstream outFile("bids.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return false;
    }

    outFile << "Item ID: " << bid.getItemId() << "\n";
    outFile << "Bidder ID: " << bid.getBidderId() << "\n";
    outFile << "Bid Amount: " << bid.getBidAmount() << "\n";
    outFile << "Time: " << bid.getBidTime() << "\n\n";

    outFile.close();
    return true;
}
