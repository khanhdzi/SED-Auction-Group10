// include/controller/BidController.h
#ifndef BID_CONTROLLER_H
#define BID_CONTROLLER_H

#include "../class/Bid.h"
#include "../dao/BidDAO.h"

class BidController {
public:
    bool placeBid(const std::string& itemId, const std::string& bidderId, double amount);
    bool placeAutomaticBid(const std::string& itemId, const std::string& bidderId, 
                          double amount, double bidLimit);
    bool validateBid(const std::string& itemId, const std::string& bidderId, double amount);
    
private:
    BidDAO bidDAO;
};

#endif
