#include "ItemListingHandler.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor initializes the handler and loads items
ItemListingHandler::ItemListingHandler(const string& file) : itemIdCounter(1), dataController(file) {
    loadListings();
}

// Create a new item
void ItemListingHandler::createListing() {
    string name, category, description;
    int startingBid, bidIncrement, minBuyerRating, duration;

    cout << "\nEnter details for the new item:\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Category: ";
    getline(cin, category);

    cout << "Description: ";
    getline(cin, description);

    cout << "Starting Bid: ";
    cin >> startingBid;

    cout << "Bid Increment: ";
    cin >> bidIncrement;

    cout << "Auction Duration (in hours): ";
    cin >> duration;

    cout << "Minimum Buyer Rating: ";
    cin >> minBuyerRating;

    time_t endTime = time(nullptr) + duration * 3600;

    ItemListing newItem(itemIdCounter++, name, category, description, startingBid, bidIncrement, endTime, minBuyerRating);
    listings.push_back(newItem);
    saveListings();
    cout << "Item created successfully!\n";
}

// Display all items
void ItemListingHandler::viewListings() {
    if (listings.empty()) {
        cout << "No items to display.\n";
        return;
    }

    cout << "\nCurrent Listings:\n";
    for (const auto& item : listings) {
        cout << "ID: " << item.id << "\n"
             << "Name: " << item.name << "\n"
             << "Category: " << item.category << "\n"
             << "Description: " << item.description << "\n"
             << "Starting Bid: " << item.startingBid << "\n"
             << "Bid Increment: " << item.bidIncrement << "\n"
             << "Ends: " << put_time(localtime(&item.endTime), "%Y-%m-%d %H:%M:%S") << "\n"
             << "Min Buyer Rating: " << item.minBuyerRating << "\n"
             << "--------------------\n";
    }
}

// Delete an item by ID
void ItemListingHandler::deleteListing(int itemId) {
    // Use remove_if to find the items to be removed
    auto it = remove_if(listings.begin(), listings.end(), [itemId](const ItemListing& item) {
        return item.id == itemId; // Match the item with the given ID
    });

    if (it != listings.end()) { // Check if any items were found
        listings.erase(it, listings.end()); // Erase the items from the vector
        saveListings(); // Save the updated list to the file
        cout << "Item with ID " << itemId << " deleted successfully.\n";
    } else {
        cout << "No item found with ID " << itemId << ".\n";
    }
}


// Update an item by ID
void ItemListingHandler::updateListing(int itemId) {
    for (auto& item : listings) {
        if (item.id == itemId) {
            cout << "Updating item...\n";
            cout << "New Name: ";
            cin.ignore();
            getline(cin, item.name);
            cout << "New Category: ";
            getline(cin, item.category);
            cout << "New Starting Bid: ";
            cin >> item.startingBid;
            saveListings();
            cout << "Item updated successfully.\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

// Save listings to the file
void ItemListingHandler::saveListings() {
    dataController.saveToFile(listings);
}

// Load listings from the file
void ItemListingHandler::loadListings() {
    listings = dataController.loadFromFile();
}
