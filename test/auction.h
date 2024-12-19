#ifndef AUCTION_H
#define AUCTION_H

#include <vector>
#include <string>
#include <iostream>
#include "Item.h"
using namespace std;

class Auction {
private:
    vector<Item> items;

public:
    void addItem(const Item &item) { items.push_back(item); }

    Item* getItemByID(const string &itemID) {
        for (auto &item : items) {
            if (item.getItemID() == itemID) {
                return &item;
            }
        }
        return nullptr;
    }

    void listItems() {
        for (const auto &item : items) {
            cout << "Item ID: " << item.getItemID()
                 << ", Name: " << item.getName()
                 << ", Starting Price: " << item.getStartingPrice()
                 << ", Current Highest Bid: " << item.getHighestBid() << endl;
        }
    }
};

#endif
