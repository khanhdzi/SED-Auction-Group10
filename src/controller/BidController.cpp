#include "../../include/controller/BidController.h"
#include <iomanip>

// Place a bid
void BidController::placeBid() {
    if (!Authenticator::isLoggedIn()) {
        std::cerr << "Error: You must be logged in to place a bid.\n";
        return;
    }

    User* bidder = Authenticator::getLoggedUser();

    // Validate item ID
   std::string itemId = InputValidator::validateExistingItemID("Enter the Item ID to place a bid: ", itemDAO);

    auto itemOpt = itemDAO.findItemById(itemId);

    if (!itemOpt) {
        std::cerr << "Error: Item not found.\n";
        return;
    }

    auto item = itemOpt.value();

    // Check if auction is active
    if (item.getStatus() == "closed" || std::chrono::system_clock::now() >= item.getEndTime()) {
        std::cerr << "Error: Auction for this item is already closed.\n";
        return;
    }

    // Get bid amount
    double bidAmount = InputValidator::validateDouble("Enter your bid amount: ", 
                          item.getCurrentBid() + item.getBidIncrement(), 1e6);

    // Check if bidder has sufficient credit points
    if (!hasSufficientCreditPoints(bidAmount)) {
        std::cerr << "Error: Insufficient credit points to place the bid.\n";
        return;
    }

    // Place the bid
    Bid newBid(itemId, bidder->getUsername(), bidAmount);
    if (bidDAO.placeBid(newBid)) {
        item.setCurrentBid(bidAmount, bidder->getUsername());
        itemDAO.addItem(item);
        bidder->setCreditPoints(bidder->getCreditPoints() - bidAmount);
        userDAO.updateUser(*bidder);
        std::cout << "Bid placed successfully.\n";
    } else {
        std::cerr << "Failed to place bid.\n";
    }
}

// View all bids for a specific item
void BidController::viewBidsForItem() {
    std::string itemId = InputValidator::validateExistingItemID("Enter the Item ID to view bids: ", itemDAO);
    auto bids = bidDAO.findBidsByItemId(itemId);

    std::cout << "Bids for Item ID: " << itemId << "\n";
    displayBids(bids);
}

// View active bids placed by the logged-in user
void BidController::viewUserBids() const {
    if (!Authenticator::isLoggedIn()) {
        std::cerr << "Error: You must be logged in to view your bids.\n";
        return;
    }

    User* bidder = Authenticator::getLoggedUser();
    auto bids = bidDAO.getActiveBidsByUser(bidder->getUsername());
    std::cout << "Active Bids for User: " << bidder->getUsername() << "\n";
    displayBids(bids);
}

// Finalize an auction
void BidController::finalizeAuction(const std::string& itemId) {
    auto itemOpt = itemDAO.findItemById(itemId);
    if (!itemOpt) {
        std::cerr << "Error: Item not found.\n";
        return;
    }

    auto item = itemOpt.value();

    if (item.getStatus() == "closed") {
        std::cerr << "Error: Auction is already closed.\n";
        return;
    }

    auto highestBid = bidDAO.getHighestBid(itemId);
    if (!highestBid) {
        std::cerr << "No bids were placed on this item.\n";
        return;
    }

    auto bidderOpt = userDAO.findUserById(highestBid->getBidderId());
    auto sellerOpt = userDAO.findUserById(item.getSellerID());

    if (!bidderOpt || !sellerOpt) {
        std::cerr << "Error: Could not retrieve buyer or seller information.\n";
        return;
    }

    User bidder = bidderOpt.value();
    User seller = sellerOpt.value();

    // Update item status
    item.closeAuction();
    itemDAO.addItem(item);

    // Allow mutual rating
    double sellerRating = InputValidator::validateDouble("Rate the seller (1-5): ", 1.0, 5.0);
    double buyerRating = InputValidator::validateDouble("Rate the buyer (1-5): ", 1.0, 5.0);

    RatingRecord sellerRecord(bidder.getUsername(), seller.getUsername(), sellerRating, false);
    RatingRecord buyerRecord(seller.getUsername(), bidder.getUsername(), buyerRating, true);

    RatingDAO ratingDAO;
    ratingDAO.saveRating(sellerRecord);
    ratingDAO.saveRating(buyerRecord);

    std::cout << "Auction finalized and ratings submitted successfully.\n";
}

// Display bids
void BidController::displayBids(const std::vector<Bid>& bids) const {
    if (bids.empty()) {
        std::cout << "No bids available.\n";
        return;
    }

    std::cout << std::left << std::setw(15) << "Item ID"
              << std::setw(15) << "Bidder"
              << std::setw(10) << "Amount"
              << std::setw(25) << "Bid Time\n";
    std::cout << std::string(65, '-') << "\n";

    for (const auto& bid : bids) {
        std::time_t bidTime = std::chrono::system_clock::to_time_t(bid.getBidTime());
        std::cout << std::left << std::setw(15) << bid.getItemId()
                  << std::setw(15) << bid.getBidderId()
                  << "$" << std::setw(9) << bid.getBidAmount()
                  << std::ctime(&bidTime);
    }
}

// Check credit points
bool BidController::hasSufficientCreditPoints(double bidAmount) const {
    User* bidder = Authenticator::getLoggedUser();
    return bidder->getCreditPoints() >= bidAmount;
}
