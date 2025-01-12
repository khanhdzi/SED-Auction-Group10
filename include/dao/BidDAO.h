#ifndef BID_DAO_H
#define BID_DAO_H

#include "../class/Bid.h"

class BidDAO {
public:
    bool placeBid(const Bid& bid);
};

#endif
