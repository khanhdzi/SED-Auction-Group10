#include "ItemDataController.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor with filename
ItemDataController::ItemDataController(const string& file) : filename(file) {}

// Save all items to the file
void ItemDataController::saveToFile(const vector<ItemListing>& items) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Couldn't open file for writing." << endl;
        return;
    }

    for (const auto& item : items) {
        file << item.id << "|"
             << item.name << "|"
             << item.category << "|"
             << item.description << "|"
             << item.startingBid << "|"
             << item.bidIncrement << "|"
             << item.endTime << "|"
             << item.minBuyerRating << endl;
    }
    file.close();
}

// Load all items from the file
vector<ItemListing> ItemDataController::loadFromFile() {
    ifstream file(filename);
    vector<ItemListing> items;

    if (!file) {
        cerr << "Error: Couldn't open file for reading. Returning an empty list." << endl;
        return items;
    }

    string line;
    while (getline(file, line)) {
        ItemListing item;
        istringstream stream(line);
        string token;

        getline(stream, token, '|');
        item.id = stoi(token);

        getline(stream, item.name, '|');
        getline(stream, item.category, '|');
        getline(stream, item.description, '|');

        getline(stream, token, '|');
        item.startingBid = stoi(token);

        getline(stream, token, '|');
        item.bidIncrement = stoi(token);

        getline(stream, token, '|');
        item.endTime = stoll(token);

        getline(stream, token, '|');
        item.minBuyerRating = stoi(token);

        items.push_back(item);
    }
    file.close();
    return items;
}
