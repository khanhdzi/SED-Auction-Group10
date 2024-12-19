#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item {
private:
    string itemID;
    string name;
    string description;
    double startingPrice;
    double highestBid;
    string highestBidder;

public:
    Item(string id, string n, string desc, double price)
        : itemID(id), name(n), description(desc), startingPrice(price), highestBid(price), highestBidder("") {}

    string getItemID() const { return itemID; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getStartingPrice() const { return startingPrice; }
    double getHighestBid() const { return highestBid; }
    string getHighestBidder() const { return highestBidder; }

    void placeBid(const string& bidder, double bid) {
        if (bid > highestBid) {
            highestBid = bid;
            highestBidder = bidder;
        }
    }
};

#endif
