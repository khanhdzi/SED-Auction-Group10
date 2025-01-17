#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <chrono>
#include <fstream>

class Item {
public:
    // Existing parameterized constructor
    Item(std::string name, std::string category, std::string description, 
         double startingBid, double bidIncrement, 
         std::chrono::system_clock::time_point endTime, int minBuyerRating, 
         const std::string& sellerID);

    // Default constructor
    Item();

    // Getters
    std::string getItemID() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getDescription() const;
    double getStartingBid() const;
    double getBidIncrement() const;
    double getCurrentBid() const;
    std::string getCurrentBidder() const;
    std::chrono::system_clock::time_point getEndTime() const;
    int getMinBuyerRating() const;
    std::string getStatus() const;
    std::string getSellerID() const; // New getter for seller ID

    // Setters
    void setCurrentBid(double bid, const std::string& bidder);
    void setDescription(const std::string& newDescription);
    void setStartingBid(double newStartingBid);
    void setCurrentBidder(const std::string& bidder);
    void closeAuction();

    // Serialization and Deserialization
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);

    // Static Utility for ID generation
    static std::string generateItemID();

private:
    std::string itemID;  // Unique ID for the item
    std::string name;
    std::string category;
    std::string description;
    double startingBid;
    double bidIncrement;
    double currentBid;
    std::string currentBidder;
    std::chrono::system_clock::time_point endTime;
    int minBuyerRating;
    std::string status; // "active" or "closed"
    std::string sellerID; // New field for seller ID
};

#endif // ITEM_H
