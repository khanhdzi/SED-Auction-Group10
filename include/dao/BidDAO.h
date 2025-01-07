// include/dao/BidDAO.h
#ifndef BID_DAO_H
#define BID_DAO_H

#include <vector>
#include "../class/Bid.h"

class BidDAO {
public:
    bool placeBid(const Bid& bid);
    bool updateBid(const Bid& bid);
    std::vector<Bid> getBidsForItem(const std::string& itemId);
    Bid getHighestBid(const std::string& itemId);
    bool checkAutomaticBidConflict(const std::string& itemId, double bidLimit);
    void processAutomaticBids(const std::string& itemId, double newBidAmount);
    
private:
    void saveBidsToFile();
    void loadBidsFromFile();
};

#endif
