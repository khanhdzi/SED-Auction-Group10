#ifndef BID_H
#define BID_H

#include <string>
#include <ctime>
#include <fstream>

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
    std::time_t getBidTime() const;

    // Setters
    void setAutomaticBidLimit(double bidLimit);

    // Serialization
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);

private:
    std::string itemId;
    std::string bidderId;
    double bidAmount;
    double automaticBidLimit;
    std::time_t bidTime;  // Stores the time of bid placement
};

#endif
