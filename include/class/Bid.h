#ifndef BID_H
#define BID_H

#include <string>
#include <chrono>
#include <fstream>

class Bid {
public:
    // Default constructor
    Bid();

    // Parameterized constructor
    Bid(const std::string& itemId, const std::string& bidderId, double bidAmount, 
        double automaticBidLimit = 0.0);

    // Getters
    std::string getItemId() const;
    std::string getBidderId() const;
    double getBidAmount() const;
    std::chrono::system_clock::time_point getBidTime() const;
    double getAutomaticBidLimit() const;

    // Setters
    void setAutomaticBidLimit(double bidLimit);

    // Comparison operator for sorting bids
    bool operator<(const Bid& other) const;

    // Serialization and Deserialization
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);

private:
    std::string itemId;
    std::string bidderId;
    double bidAmount;
    std::chrono::system_clock::time_point bidTime;
    double automaticBidLimit;
};

#endif // BID_H
