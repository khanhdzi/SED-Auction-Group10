#ifndef BID_CONTROLLER_H
#define BID_CONTROLLER_H

#include "../dao/BidDAO.h"
#include "../dao/UserDataHandler.h"
#include "../dao/ItemDAO.h"
#include "../class/Bid.h"
#include "../class/User.h"
#include "../class/Item.h"
#include <string>
#include <vector>
#include <iostream>

class BidController {
public:
    // Constructor that initializes DAO objects
    BidController();

    // Function to place a bid for an item by a user
    bool placeBid(const std::string& itemId, const std::string& bidderId, double amount);

    // Function to search for items by name, category, or credit point range
    std::vector<Item> searchItems(const std::string& name = "", const std::string& category = "",
                                  double minPoints = 0, double maxPoints = 1000);

    // Function to view details of a specific item
    void viewItemDetails(const std::string& itemId);

    // Function to conclude the auction and process the winning bid
    void concludeAuction(const std::string& itemId); // Declaration added

private:
    // Function to validate bid: checks if user has enough credit points for the bid
    bool validateBid(const std::string& itemId, const std::string& bidderId, double amount);

    // Check if the user has enough credit points for all active bids
    bool hasSufficientCreditForAllBids(const std::string& bidderId, double bidAmount);

    // DAO objects for accessing data
    BidDAO bidDAO;
    UserDataHandler userDAO;
    ItemDAO itemDAO;
};

#endif // BID_CONTROLLER_H
