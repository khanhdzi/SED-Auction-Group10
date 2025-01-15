#include "../../include/class/Item.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Constructor
Item::Item(std::string name, std::string category, std::string description, 
           double startingBid, double bidIncrement, 
           std::chrono::system_clock::time_point endTime, int minBuyerRating)
    : name(name), description(description), startingBid(startingBid), 
      bidIncrement(bidIncrement), currentBid(startingBid), currentBidder(""),
      creationTime(std::chrono::system_clock::now()), endTime(endTime), 
      minBuyerRating(minBuyerRating), status("active") {
    
    // Validate category
    if (!Category::isValidCategory(category)) {
        throw std::invalid_argument("Invalid category: " + category);
    }

    this->category = category;
}


// Getters
std::string Item::getName() const { return name; }
std::string Item::getCategory() const { return category; }
std::string Item::getDescription() const { return description; }
double Item::getStartingBid() const { return startingBid; }
double Item::getBidIncrement() const { return bidIncrement; }
double Item::getCurrentBid() const { return currentBid; }
std::string Item::getCurrentBidder() const { return currentBidder; }
std::chrono::system_clock::time_point Item::getEndTime() const { return endTime; }
std::chrono::system_clock::time_point Item::getCreationTime() const { return creationTime; }
int Item::getMinBuyerRating() const { return minBuyerRating; }
std::string Item::getStatus() const { return status; }

// Setters
void Item::setStartingBid(double newStartingBid) { 
    if (status == "active" && currentBid == startingBid) {
        startingBid = newStartingBid; 
        currentBid = newStartingBid; 
    }
}

void Item::setBidIncrement(double newBidIncrement) { 
    if (status == "active") {
        bidIncrement = newBidIncrement; 
    }
}

void Item::setCurrentBid(double bid, const std::string& bidder) {
    currentBid = bid;
    currentBidder = bidder;
}

void Item::closeAuction() { 
    status = "closed"; 
}

// Auction Logic
bool Item::isActive() const {
    return status == "active" && std::chrono::system_clock::now() < endTime;
}

bool Item::placeBid(double bid, const std::string& bidder) {
    if (!isActive()) {
        std::cout << "Auction is not active. Bidding not allowed.\n";
        return false;
    }
    if (bid < currentBid + bidIncrement) {
        std::cout << "Bid must be at least " << bidIncrement << " higher than the current bid.\n";
        return false;
    }
    setCurrentBid(bid, bidder);
    std::cout << "Bid placed successfully by " << bidder << ".\n";
    return true;
}

// Serialization
void Item::serialize(std::ofstream& file) const {
    size_t length;

    // Write name
    length = name.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(name.c_str(), length);

    // Write category
    length = category.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(category.c_str(), length);

    // Write description
    length = description.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(description.c_str(), length);

    // Write other fields
    file.write(reinterpret_cast<const char*>(&startingBid), sizeof(startingBid));
    file.write(reinterpret_cast<const char*>(&bidIncrement), sizeof(bidIncrement));
    file.write(reinterpret_cast<const char*>(&currentBid), sizeof(currentBid));

    // Write timestamps
    auto creationTimeT = std::chrono::system_clock::to_time_t(creationTime);
    auto endTimeT = std::chrono::system_clock::to_time_t(endTime);
    file.write(reinterpret_cast<const char*>(&creationTimeT), sizeof(creationTimeT));
    file.write(reinterpret_cast<const char*>(&endTimeT), sizeof(endTimeT));

    // Write ratings and status
    file.write(reinterpret_cast<const char*>(&minBuyerRating), sizeof(minBuyerRating));
    length = status.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(status.c_str(), length);
}

void Item::deserialize(std::ifstream& file) {
   size_t length;
    char buffer[1024]; // Buffer for reading strings

    // Read name
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    name = buffer;

    // Read category
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    std::string tempCategory = buffer;

    // Validate category
    if (!Category::isValidCategory(tempCategory)) {
        throw std::invalid_argument("Invalid category in data: " + tempCategory);
    }
    category = tempCategory;

    // Read description
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    description = buffer;

    // Read other fields
    file.read(reinterpret_cast<char*>(&startingBid), sizeof(startingBid));
    file.read(reinterpret_cast<char*>(&bidIncrement), sizeof(bidIncrement));
    file.read(reinterpret_cast<char*>(&currentBid), sizeof(currentBid));

    // Read timestamps
    std::time_t creationTimeT;
    std::time_t endTimeT;
    file.read(reinterpret_cast<char*>(&creationTimeT), sizeof(creationTimeT));
    file.read(reinterpret_cast<char*>(&endTimeT), sizeof(endTimeT));
    creationTime = std::chrono::system_clock::from_time_t(creationTimeT);
    endTime = std::chrono::system_clock::from_time_t(endTimeT);

    // Read ratings and status
    file.read(reinterpret_cast<char*>(&minBuyerRating), sizeof(minBuyerRating));
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    status = buffer;
}