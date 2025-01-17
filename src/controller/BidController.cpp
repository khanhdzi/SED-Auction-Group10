#include "../../include/controller/BidController.h"
#include "../../include/controller/ItemDataController.h"
#include <iomanip>


ItemDataController itemController;
// Place a bid
void BidController::placeBid() {


    if (!Authenticator::isLoggedIn()) {
        std::cerr << "Error: You must be logged in to place a bid.\n";
        return;
    }

    User* bidder = Authenticator::getLoggedUser();
    std::cout << "Debug: Logged-in user: " << bidder->getUsername() 
              << ", Credit Points: " << bidder->getCreditPoints() << "\n";

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
    double bidAmount = InputValidator::validateDouble(
        "Enter your bid amount: ",
        item.getCurrentBid() + item.getBidIncrement(),
        1e6
    );

    // Check if bidder has sufficient credit points
    if (!hasSufficientCreditPoints(bidAmount)) {
        std::cerr << "Error: Insufficient credit points to place the bid.\n";
        return;
    }

    // Check buyer rating
    if (bidder->getBuyerRating() < item.getMinBuyerRating()) {
        std::cerr << "Error: Your buyer rating is too low to place a bid.\n";
        return;
    }

    // Place the bid
    Bid newBid(itemId, bidder->getUsername(), bidAmount);
    if (bidDAO.placeBid(newBid)) {
    

        // Update item details
        item.setCurrentBid(bidAmount, bidder->getUsername());
        if (!itemDAO.updateItem(item)) {
            std::cerr << "Error: Failed to update item after placing the bid.\n";
            return;
        }

        // Deduct credit points from bidder and update their record
        bidder->setCreditPoints(bidder->getCreditPoints() - bidAmount);
        if (!userDAO.updateUser(*bidder)) {
            std::cerr << "Error: Failed to update user credit points.\n";
            return;
        }

        std::cout << "Debug: Bidder's new credit points: " << bidder->getCreditPoints() << "\n";
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

void BidController::finalizeAuction(const std::string& itemId) {
    std::cout << "Debug: Finalizing auction for Item ID: " << itemId << "\n";

    if (!Authenticator::isLoggedIn()) {
        std::cerr << "Error: You must be logged in to finalize an auction.\n";
        return;
    }

    User* loggedUser = Authenticator::getLoggedUser();
    auto itemOpt = itemDAO.findItemById(itemId);
    if (!itemOpt) {
        std::cerr << "Error: Item not found.\n";
        return;
    }
    auto item = itemOpt.value();

    // Check if the logged-in user is the seller
    if (item.getSellerID() != loggedUser->getUsername()) {
        std::cerr << "Error: You can only finalize auctions for your own items.\n";
        return;
    }

    if (item.getStatus() == "closed") {
        std::cerr << "Error: Auction for this item is already finalized.\n";
        return;
    }

    auto highestBidOpt = bidDAO.getHighestBid(itemId);
    if (!highestBidOpt) {
        std::cout << "No bids were placed for this item. Auction closed with no winner.\n";
        item.closeAuction();
        if (!itemDAO.updateItem(item)) {
            std::cerr << "Error: Failed to update item status.\n";
        }
        return;
    }
    auto highestBid = highestBidOpt.value();

    std::cout << "Debug: Highest bid amount: " << highestBid.getBidAmount()
              << ", Bidder ID: " << highestBid.getBidderId() << "\n";

    item.closeAuction();

    if (!itemDAO.updateItem(item)) {
        std::cerr << "Error: Failed to update item status.\n";
        return;
    }

    itemController.saveListingsToFile();
    std::cout << "Auction finalized successfully. Winner: " << highestBid.getBidderId() << "\n";
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

std::vector<Bid> BidController::getActiveBidsForUser(const std::string& username) const {
    return bidDAO.getActiveBidsByUser(username);
}
