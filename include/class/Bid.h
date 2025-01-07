// include/class/Bid.h
#ifndef BID_H
#define BID_H

#include <string>
#include <ctime>

class Bid {
private:
    int bidId;
    std::string itemId;
    std::string bidderId;
    double bidAmount;
    time_t bidTime;
    double automaticBidLimit;  // For advanced feature

public:
    Bid(const std::string& itemId, const std::string& bidderId, double amount);
    Bid(const std::string& itemId, const std::string& bidderId, double amount, double bidLimit);
    
    // Getters
    int getBidId() const;
    std::string getItemId() const;
    std::string getBidderId() const;
    double getBidAmount() const;
    time_t getBidTime() const;
    double getAutomaticBidLimit() const;
    
    // Setters
    void setBidAmount(double amount);
    void setAutomaticBidLimit(double limit);
};

#endif
