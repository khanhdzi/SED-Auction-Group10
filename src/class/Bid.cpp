#include "../../include/class/Bid.h"
#include <iostream>
#include <sstream>

// Default constructor
Bid::Bid()
    : itemId(""), bidderId(""), bidAmount(0.0), bidTime(std::chrono::system_clock::now()), automaticBidLimit(0.0) {}

// Parameterized constructor
Bid::Bid(const std::string& itemId, const std::string& bidderId, double bidAmount, double automaticBidLimit)
    : itemId(itemId), bidderId(bidderId), bidAmount(bidAmount), bidTime(std::chrono::system_clock::now()), 
      automaticBidLimit(automaticBidLimit) {}

// Getters
std::string Bid::getItemId() const {
    return itemId;
}

std::string Bid::getBidderId() const {
    return bidderId;
}

double Bid::getBidAmount() const {
    return bidAmount;
}

std::chrono::system_clock::time_point Bid::getBidTime() const {
    return bidTime;
}

double Bid::getAutomaticBidLimit() const {
    return automaticBidLimit;
}

// Setters
void Bid::setAutomaticBidLimit(double bidLimit) {
    automaticBidLimit = bidLimit;
}

// Comparison operator
bool Bid::operator<(const Bid& other) const {
    return bidAmount < other.bidAmount;
}

// Serialization
void Bid::serialize(std::ofstream& file) const {
    size_t length;

    length = itemId.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(itemId.c_str(), length);

    length = bidderId.size();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    file.write(bidderId.c_str(), length);

    file.write(reinterpret_cast<const char*>(&bidAmount), sizeof(bidAmount));

    auto bidTimeT = std::chrono::system_clock::to_time_t(bidTime);
    file.write(reinterpret_cast<const char*>(&bidTimeT), sizeof(bidTimeT));

    file.write(reinterpret_cast<const char*>(&automaticBidLimit), sizeof(automaticBidLimit));
}

// Deserialization
void Bid::deserialize(std::ifstream& file) {
    size_t length;
    char buffer[1024];

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    itemId = buffer;

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    file.read(buffer, length);
    buffer[length] = '\0';
    bidderId = buffer;

    file.read(reinterpret_cast<char*>(&bidAmount), sizeof(bidAmount));

    std::time_t bidTimeT;
    file.read(reinterpret_cast<char*>(&bidTimeT), sizeof(bidTimeT));
    bidTime = std::chrono::system_clock::from_time_t(bidTimeT);

    file.read(reinterpret_cast<char*>(&automaticBidLimit), sizeof(automaticBidLimit));
}
