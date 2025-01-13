#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    // Constructor
    Item(const std::string& itemId, const std::string& name, double price, const std::string& category);

    // Getter methods
    std::string getItemId() const;
    std::string getName() const;
    double getPrice() const;
    std::string getCategory() const;
    double getHighestBid() const;
    std::string getHighestBidder() const;
    std::string getEndDate() const;
    int getCreditPoints() const;  // Assuming this method is required for credit points

private:
    std::string itemId;        // Unique identifier for the item
    std::string name;          // Name of the item
    double price;              // Price of the item
    std::string category;      // Category to which the item belongs
    int creditPoints;          // Member variable for credit points
    double highestBid;         // Member variable for highest bid
    std::string highestBidder; // Member variable for highest bidder
    std::string endDate;       // Member variable for auction end date (can be a string or time)
};

#endif  // ITEM_H
