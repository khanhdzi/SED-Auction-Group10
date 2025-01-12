#ifndef BID_CONTROLLER_H
#define BID_CONTROLLER_H

#include "../dao/BidDAO.h"
#include "../class/Bid.h"
#include <string>

class BidController {
public:
    bool placeBid(const std::string& itemId, const std::string& bidderId, double amount);

private:
    bool validateBid(const std::string& itemId, const std::string& bidderId, double amount);
    BidDAO bidDAO;
};

#endif
