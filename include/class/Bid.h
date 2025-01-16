#ifndef BID_H
#define BID_H

#include <string>
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

class Bid {
public:
    // Default constructor
    Bid();

    // Parameterized constructors
    Bid(const std::string& itemId, const std::string& bidderId, double amount);
    Bid(const std::string& itemId, const std::string& bidderId, double amount, double bidLimit);

    // Getters
    std::string getItemId() const;
    std::string getBidderId() const;
    double getBidAmount() const;
    double getAutomaticBidLimit() const;
    std::chrono::system_clock::time_point getBidTime() const;

    // Setters
    void setAutomaticBidLimit(double bidLimit);

    // Comparison operator (for sorting or finding highest bid)
    bool operator<(const Bid& other) const;

    // Serialization
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);

private:
    std::string itemId;             // ID of the item being bid on
    std::string bidderId;           // ID of the bidder
    double bidAmount;               // Amount of the bid
    double automaticBidLimit;       // Maximum bid amount for automatic bidding
    std::chrono::system_clock::time_point bidTime;  // Time of bid placement
};

#endif // BID_H
