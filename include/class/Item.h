// include/class/Item.h

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <chrono>
#include <fstream>
#include "../utils/Category.h"  // Include the Category class


class Item {
public:
    // Constructor
    Item(std::string name, std::string category, std::string description, 
         double startingBid, double bidIncrement, std::chrono::system_clock::time_point endTime, 
         int minBuyerRating);

    // Getters
    std::string getName() const;
    std::string getCategory() const;
    std::string getDescription() const;
    double getStartingBid() const;
    double getBidIncrement() const;
    std::chrono::system_clock::time_point getEndTime() const;
    int getMinBuyerRating() const;
    double getCurrentBid() const;
    std::string getCurrentBidder() const;
    std::chrono::system_clock::time_point getCreationTime() const;
    std::string getStatus() const;

    // Setters
    void setStartingBid(double newStartingBid);
    void setBidIncrement(double newBidIncrement);
    void setCurrentBid(double bid, const std::string& bidder);
    void closeAuction();

    // Auction Logic
    bool isActive() const;
    bool placeBid(double bid, const std::string& bidder);

    // Serialization and Deserialization
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);

private:
    std::string name;
    std::string category;
    std::string description;
    double startingBid;
    double bidIncrement;
    double currentBid;           // Tracks the current highest bid
    std::string currentBidder;   // Tracks the username of the current highest bidder
    std::chrono::system_clock::time_point creationTime;
    std::chrono::system_clock::time_point endTime;
    int minBuyerRating;
    std::string status;          // "active", "closed", or "cancelled"
};

#endif // ITEM_H