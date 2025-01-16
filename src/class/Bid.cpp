#include "../../include/class/Bid.h"
#include <chrono> // Include for std::chrono
#include <iomanip>
#include <sstream>

// Default constructor
Bid::Bid() 
    : itemId(""), bidderId(""), bidAmount(0.0), automaticBidLimit(0.0), bidTime(std::chrono::system_clock::now()) {}

// Parameterized constructors
Bid::Bid(const std::string& itemId, const std::string& bidderId, double amount)
    : itemId(itemId), bidderId(bidderId), bidAmount(amount), automaticBidLimit(0.0), bidTime(std::chrono::system_clock::now()) {}

Bid::Bid(const std::string& itemId, const std::string& bidderId, double amount, double bidLimit)
    : itemId(itemId), bidderId(bidderId), bidAmount(amount), automaticBidLimit(bidLimit), bidTime(std::chrono::system_clock::now()) {}

// Getters
std::string Bid::getItemId() const { return itemId; }
std::string Bid::getBidderId() const { return bidderId; }
double Bid::getBidAmount() const { return bidAmount; }
double Bid::getAutomaticBidLimit() const { return automaticBidLimit; }
std::chrono::system_clock::time_point Bid::getBidTime() const { return bidTime; }

// Setters
void Bid::setAutomaticBidLimit(double bidLimit) { automaticBidLimit = bidLimit; }

// Comparison operator
bool Bid::operator<(const Bid& other) const {
    return bidAmount < other.bidAmount;
}

// Serialization
void Bid::serialize(std::ofstream& file) const {
    size_t length;

    // Serialize itemId
    length = itemId.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(itemId.c_str(), length);

    // Serialize bidderId
    length = bidderId.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(bidderId.c_str(), length);

    // Serialize bidAmount
    file.write(reinterpret_cast<const char*>(&bidAmount), sizeof(bidAmount));

    // Serialize automaticBidLimit
    file.write(reinterpret_cast<const char*>(&automaticBidLimit), sizeof(automaticBidLimit));

    // Serialize bidTime
    auto time = std::chrono::system_clock::to_time_t(bidTime);
    file.write(reinterpret_cast<const char*>(&time), sizeof(time));
}

// Deserialization
void Bid::deserialize(std::ifstream& file) {
    size_t length;
    char buffer[1024];

    // Deserialize itemId
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    itemId = buffer;

    // Deserialize bidderId
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    bidderId = buffer;

    // Deserialize bidAmount
    file.read(reinterpret_cast<char*>(&bidAmount), sizeof(bidAmount));

    // Deserialize automaticBidLimit
    file.read(reinterpret_cast<char*>(&automaticBidLimit), sizeof(automaticBidLimit));

    // Deserialize bidTime
    std::time_t time;
    file.read(reinterpret_cast<char*>(&time), sizeof(time));
    bidTime = std::chrono::system_clock::from_time_t(time);
}
