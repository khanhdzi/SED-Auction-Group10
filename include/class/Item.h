#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <chrono>

class Item {
public:
    // Constructor
    Item(std::string name, std::string category, std::string description, 
         double startingBid, double bidIncrement, std::chrono::system_clock::time_point endTime, 
         int minBuyerRating);

    // Getter functions
    std::string getName() const;
    std::string getCategory() const;
    std::string getDescription() const;
    double getStartingBid() const;
    double getBidIncrement() const;
    std::chrono::system_clock::time_point getEndTime() const;
    int getMinBuyerRating() const;
    std::chrono::system_clock::time_point getCreationTime() const;

    // Setter functions
    void setStartingBid(double newStartingBid);
    void setBidIncrement(double newBidIncrement);
    
private:
    std::string name;
    std::string category;
    std::string description;
    double startingBid;
    double bidIncrement;
    std::chrono::system_clock::time_point creationTime;
    std::chrono::system_clock::time_point endTime;
    int minBuyerRating;
};

#endif // ITEM_H
