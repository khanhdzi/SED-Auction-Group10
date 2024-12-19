#include "Auction.h"

void Auction::addItem(const Item &item) {
    items.push_back(item);
    cout << "Item added successfully!" << endl;
}

void Auction::listItems() {
    cout << "\n--- Auction Items ---\n";
    for (const auto &item : items) {
        item.displayItem();
    }
}

Item* Auction::getItemByID(const string &itemID) {
    for (auto &item : items) {
        if (item.getItemID() == itemID) {
            return &item;
        }
    }
    return nullptr;
}

void Auction::displayBidHistory(const string &itemID) {
    Item* item = getItemByID(itemID);
    if (item) {
        item->displayBidHistory();
    } else {
        cout << "Item not found!" << endl;
    }
}
