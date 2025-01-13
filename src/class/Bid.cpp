#include "../../include/class/Bid.h"
#include <fstream>
#include <ctime>

// Constructor Definitions
Bid::Bid(const std::string& itemId, const std::string& bidderId, double amount)
    : itemId(itemId), bidderId(bidderId), bidAmount(amount), automaticBidLimit(0) {
    bidTime = time(nullptr);
}

Bid::Bid(const std::string& itemId, const std::string& bidderId, double amount, double bidLimit)
    : itemId(itemId), bidderId(bidderId), bidAmount(amount), automaticBidLimit(bidLimit) {
    bidTime = time(nullptr);
}
// Default constructor
Bid::Bid()
    : itemId(""), bidderId(""), bidAmount(0.0), automaticBidLimit(0.0) {
    bidTime = std::time(nullptr); // Set the bid time to the current time
}

// Getters
std::string Bid::getItemId() const { return itemId; }
std::string Bid::getBidderId() const { return bidderId; }
double Bid::getBidAmount() const { return bidAmount; }
double Bid::getAutomaticBidLimit() const { return automaticBidLimit; }
std::time_t Bid::getBidTime() const { return bidTime; }

// Setters
void Bid::setAutomaticBidLimit(double bidLimit) { automaticBidLimit = bidLimit; }

// Serialization Method
void Bid::serialize(std::ofstream& file) const {
    size_t length;

    // Write itemId
    length = itemId.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(itemId.c_str(), length);

    // Write bidderId
    length = bidderId.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(bidderId.c_str(), length);

    // Write bidAmount
    file.write(reinterpret_cast<const char*>(&bidAmount), sizeof(bidAmount));

    // Write automaticBidLimit
    file.write(reinterpret_cast<const char*>(&automaticBidLimit), sizeof(automaticBidLimit));

    // Write bidTime
    file.write(reinterpret_cast<const char*>(&bidTime), sizeof(bidTime));
}

// Deserialization Method
void Bid::deserialize(std::ifstream& file) {
    size_t length;
    char buffer[1024];

    // Read itemId
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    itemId = buffer;

    // Read bidderId
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    bidderId = buffer;

    // Read bidAmount
    file.read(reinterpret_cast<char*>(&bidAmount), sizeof(bidAmount));

    // Read automaticBidLimit
    file.read(reinterpret_cast<char*>(&automaticBidLimit), sizeof(automaticBidLimit));

    // Read bidTime
    file.read(reinterpret_cast<char*>(&bidTime), sizeof(bidTime));
}
