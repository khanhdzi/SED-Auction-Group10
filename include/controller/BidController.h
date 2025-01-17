#ifndef BID_CONTROLLER_H
#define BID_CONTROLLER_H

#include "../dao/BidDAO.h"
#include "../dao/ItemListingHandler.h"
#include "../dao/userDataHandler.h"
#include "../class/Authenticator.h"
#include "../utils/InputValidator.h"
#include "../class/RatingRecord.h"
#include "../dao/RatingDAO.h"
#include <string>
#include <vector>
#include <iostream>

class BidController {
public:
    // Place a bid
    void placeBid();

    // View all bids for a specific item
    void viewBidsForItem();

    // View active bids placed by the logged-in user
    void viewUserBids() const;

    // Finalize an auction
    void finalizeAuction(const std::string& itemId);

private:
    BidDAO bidDAO;
    ItemListingHandler itemDAO;
    UserDataHandler userDAO;

    // Helper to check credit points
    bool hasSufficientCreditPoints(double bidAmount) const;

    // Display bids
    void displayBids(const std::vector<Bid>& bids) const;
};

#endif // BID_CONTROLLER_H
