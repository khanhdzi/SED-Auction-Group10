// include/class/Item.h
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <chrono>
#include <random>
#include <fstream>

class Item {
public:
    // Constructor
    Item(std::string name, std::string category, std::string description, 
         double startingBid, double bidIncrement, std::chrono::system_clock::time_point endTime, 
         int minBuyerRating);

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

    // Setters
    void setCurrentBid(double bid, const std::string& bidder);
    void setDescription(const std::string& newDescription);
    void setStartingBid(double newStartingBid);
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
};

#endif // ITEM_H