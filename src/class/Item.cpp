#include "../../include/class/Item.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>  
#include <sstream>

// Static Utility for Generating Item IDs
std::string Item::generateItemID() {
    static std::mt19937 rng(std::random_device{}());                  // Random number generator
    static std::uniform_int_distribution<int> dist(1000, 9999);      // Range of IDs

    std::ostringstream oss;
    oss << "I-" << dist(rng);                                        // Generate ID in "I-XXXX" format
    return oss.str();
}

// Constructor
Item::Item(std::string name, std::string category, std::string description, 
           double startingBid, double bidIncrement, 
           std::chrono::system_clock::time_point endTime, int minBuyerRating, 
           const std::string& sellerID)
    : itemID(generateItemID()), name(name), category(category), description(description),
      startingBid(startingBid), bidIncrement(bidIncrement), 
      currentBid(startingBid), currentBidder(""), endTime(endTime), 
      minBuyerRating(minBuyerRating), status("active"), sellerID(sellerID) {}

Item::Item()
    : itemID(generateItemID()), name(""), category(""), description(""), 
      startingBid(0.0), bidIncrement(0.0), currentBid(0.0), currentBidder(""), 
      endTime(std::chrono::system_clock::now()), minBuyerRating(0), 
      status("active"), sellerID("") {}

// Getters
std::string Item::getItemID() const { return itemID; }
std::string Item::getName() const { return name; }
std::string Item::getCategory() const { return category; }
std::string Item::getDescription() const { return description; }
double Item::getStartingBid() const { return startingBid; }
double Item::getBidIncrement() const { return bidIncrement; }
double Item::getCurrentBid() const { return currentBid; }
std::string Item::getCurrentBidder() const { return currentBidder; }
std::chrono::system_clock::time_point Item::getEndTime() const { return endTime; }
int Item::getMinBuyerRating() const { return minBuyerRating; }
std::string Item::getStatus() const { return status; }
std::string Item::getSellerID() const {
    return sellerID;
}

// Setters
void Item::setCurrentBid(double bid, const std::string& bidder) {
    currentBid = bid;
    currentBidder = bidder;
}

void Item::setDescription(const std::string& newDescription) {
    description = newDescription;
}


void Item::setCurrentBidder(const std::string& bidder) {
    currentBidder = bidder;
}




// Set the starting bid
void Item::setStartingBid(double newStartingBid) {
    if (currentBid == startingBid) { // Only allow if no bids are placed
        startingBid = newStartingBid;
        currentBid = newStartingBid; // Update the current bid to match the new starting bid
    }
}

void Item::closeAuction() {
    status = "closed";
}

// Serialization// Serialization
void Item::serialize(std::ofstream& file) const {
    size_t length;

    // Serialize itemID
    length = itemID.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(itemID.c_str(), length);

    // Serialize name
    length = name.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(name.c_str(), length);

    // Serialize category
    length = category.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(category.c_str(), length);

    // Serialize description
    length = description.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(description.c_str(), length);

    // Serialize currentBidder
    length = currentBidder.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(currentBidder.c_str(), length);

    // Serialize other numeric fields
    file.write(reinterpret_cast<const char*>(&startingBid), sizeof(startingBid));
    file.write(reinterpret_cast<const char*>(&bidIncrement), sizeof(bidIncrement));
    file.write(reinterpret_cast<const char*>(&currentBid), sizeof(currentBid));

    auto endTimeT = std::chrono::system_clock::to_time_t(endTime);
    file.write(reinterpret_cast<const char*>(&endTimeT), sizeof(endTimeT));

    file.write(reinterpret_cast<const char*>(&minBuyerRating), sizeof(minBuyerRating));

    length = status.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(status.c_str(), length);

    length = sellerID.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(sellerID.c_str(), length);
}

// Deserialization
void Item::deserialize(std::ifstream& file) {
    size_t length;
    char buffer[1024];

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    itemID = buffer;

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    name = buffer;

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    category = buffer;

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    description = buffer;

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    currentBidder = buffer;

    file.read(reinterpret_cast<char*>(&startingBid), sizeof(startingBid));
    file.read(reinterpret_cast<char*>(&bidIncrement), sizeof(bidIncrement));
    file.read(reinterpret_cast<char*>(&currentBid), sizeof(currentBid));

    std::time_t endTimeT;
    file.read(reinterpret_cast<char*>(&endTimeT), sizeof(endTimeT));
    endTime = std::chrono::system_clock::from_time_t(endTimeT);

    file.read(reinterpret_cast<char*>(&minBuyerRating), sizeof(minBuyerRating));

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    status = buffer;

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    sellerID = buffer;
}
