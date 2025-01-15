#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string itemId;
    std::string name;
    double price;
    std::string category;
    double highestBid = 0.0;
    std::string highestBidder;
    std::string endDate;
    std::string ownerId; // Add ownerId attribute
    int creditPoints;

public:
    // Constructor
    Item(const std::string& itemId, const std::string& name, double price, const std::string& category);

    // Setters
    void setHighestBid(double bid);
    void setHighestBidder(const std::string& bidder);
    void setEndDate(const std::string& endDate);
    void setOwnerId(const std::string& ownerId); // Add setter for ownerId

    // Getters
    std::string getItemId() const;
    std::string getName() const;
    double getPrice() const;
    std::string getCategory() const;
    double getHighestBid() const;
    std::string getHighestBidder() const;
    std::string getEndDate() const;
    std::string getOwnerId() const; // Add getter for ownerId
    int getCreditPoints() const;
};

#endif // ITEM_H
