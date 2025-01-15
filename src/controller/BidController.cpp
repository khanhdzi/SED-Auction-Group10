#include <algorithm> // For std::max_element
#include "../../include/controller/BidController.h"
#include "../../include/dao/ItemDAO.h"
#include "../../include/class/Item.h"
#include "../../include/controller/RatingController.h"
#include <iostream>


BidController::BidController() {
    itemDAO = ItemDAO();  // Initialize ItemDAO
    userDAO = UserDataHandler();  // Initialize UserDataHandler (assuming this is your user DAO)
    bidDAO = BidDAO();    // Initialize BidDAO
}

bool BidController::placeBid(const std::string& itemId, const std::string& bidderId, double amount) {
    // Validate if the bid is valid (amount, credit points, etc.)
    if (!validateBid(itemId, bidderId, amount)) {
        return false;
    }

    // Create a new Bid object
    Bid newBid(itemId, bidderId, amount);

    // Place the bid using the BidDAO
    return bidDAO.placeBid(newBid);
}

bool BidController::validateBid(const std::string& itemId, const std::string& bidderId, double amount) {
    // Fetch user from the UserDataHandler (DAO)
    std::optional<User> userOpt = userDAO.findUserByCredentials(bidderId, bidderId); // Assuming bidderId used for both username and password
    if (!userOpt.has_value()) {
        std::cerr << "User not found.\n";
        return false;
    }

    User user = userOpt.value();

    // Check if the user has enough credit for the bid
    if (!hasSufficientCreditForAllBids(bidderId, amount)) {
        std::cerr << "Not enough credit points.\n";
        return false;
    }

    // Further checks can go here (e.g., checking if the user is the highest bidder)
    return true;
}

bool BidController::hasSufficientCreditForAllBids(const std::string& bidderId, double bidAmount) {
    // Get all active bids by the user
    std::vector<Bid> userBids = bidDAO.getActiveBidsByUser(bidderId); // Assuming a method to fetch only active bids
    double totalBidAmount = 0.0;
    
    for (const auto& bid : userBids) {
        totalBidAmount += bid.getBidAmount();  // Sum up all the active bids
    }

    // Check if user has enough credit points for all their active bids + new bid
    std::optional<User> userOpt = userDAO.findUserByCredentials(bidderId, bidderId);
    if (userOpt.has_value()) {
        User user = userOpt.value();
        if (user.getCreditPoints() >= totalBidAmount + bidAmount) {
            return true;
        }
    }

    return false;  // User does not have sufficient credit points
}

std::vector<Item> BidController::searchItems(const std::string& name, const std::string& category, 
                                              double minPoints, double maxPoints) {
    // Use search criteria to filter items
    std::vector<Item> allItems = itemDAO.getAllItems();  // Assuming this returns all items
    std::vector<Item> filteredItems;
    
    for (const auto& item : allItems) {
        if ((name.empty() || item.getName().find(name) != std::string::npos) &&
            (category.empty() || item.getCategory() == category) &&
            (item.getCreditPoints() >= minPoints && item.getCreditPoints() <= maxPoints)) {
            filteredItems.push_back(item);
        }
    }
    
    return filteredItems;
}

void BidController::viewItemDetails(const std::string& itemId) {
    // Fetch item by ID
    std::optional<Item> itemOpt = itemDAO.findItemById(itemId);
    if (itemOpt.has_value()) {
        Item item = itemOpt.value();
        std::cout << "Item ID: " << item.getItemId() << "\n";
        std::cout << "Item Name: " << item.getName() << "\n";
        std::cout << "Current Highest Bid: " << item.getHighestBid() << "\n";
        std::cout << "Highest Bidder: " << item.getHighestBidder() << "\n";
        std::cout << "Auction End Date: " << item.getEndDate() << "\n";
    } else {
        std::cerr << "Item not found!\n";
    }
}


void BidController::concludeAuction(const std::string& itemId) {
    // Fetch all bids for the item
    std::vector<Bid> bids = bidDAO.findBidsByItemId(itemId);
    if (bids.empty()) {
        std::cerr << "No bids found for this item.\n";
        return;
    }

    // Find the highest bid
    Bid highestBid = *std::max_element(bids.begin(), bids.end(),
                                       [](const Bid& a, const Bid& b) {
                                           return a.getBidAmount() < b.getBidAmount();
                                       });

    // Fetch the winning bidder and the seller
    std::optional<User> winnerOpt = userDAO.findUserByCredentials(highestBid.getBidderId(), "");
    std::optional<Item> itemOpt = itemDAO.findItemById(itemId);

    if (!winnerOpt.has_value() || !itemOpt.has_value()) {
        std::cerr << "Winner or item not found.\n";
        return;
    }

    User winner = winnerOpt.value();
    Item item = itemOpt.value();

    std::optional<User> sellerOpt = userDAO.findUserByCredentials(item.getOwnerId(), "");
    if (!sellerOpt.has_value()) {
        std::cerr << "Seller not found.\n";
        return;
    }

    User seller = sellerOpt.value();

    // Transfer credit points
    double amount = highestBid.getBidAmount();
    if (winner.getCreditPoints() < amount) {
        std::cerr << "Insufficient credit points for the transaction.\n";
        return;
    }

    winner.setCreditPoints(winner.getCreditPoints() - amount);
    seller.setCreditPoints(seller.getCreditPoints() + amount);

    // Save updated users
    userDAO.saveUser(winner);
    userDAO.saveUser(seller);

    // Trigger ratings
    RatingController ratingController;
    double sellerRating, buyerRating;

    std::cout << "Please rate the seller (1-5): ";
    std::cin >> sellerRating;
    ratingController.rateUser(winner.getUsername(), seller.getUsername(), sellerRating, true);

    std::cout << "Please rate the buyer (1-5): ";
    std::cin >> buyerRating;
    ratingController.rateUser(seller.getUsername(), winner.getUsername(), buyerRating, false);

    std::cout << "Auction concluded successfully!\n";
}