#include "../../include/class/Item.h"
#include<iostream>

#include <chrono>

Item::Item(std::string name, std::string category, std::string description, 
           double startingBid, double bidIncrement, std::chrono::system_clock::time_point endTime, 
           int minBuyerRating)
    : name(name), category(category), description(description), 
      startingBid(startingBid), bidIncrement(bidIncrement), 
      endTime(endTime), minBuyerRating(minBuyerRating) {
    creationTime = std::chrono::system_clock::now();  // Automatically record the creation time
}

std::string Item::getName() const {
    return name;
}

std::string Item::getCategory() const {
    return category;
}

std::string Item::getDescription() const {
    return description;
}

double Item::getStartingBid() const {
    return startingBid;
}

double Item::getBidIncrement() const {
    return bidIncrement;
}

std::chrono::system_clock::time_point Item::getEndTime() const {
    return endTime;
}

int Item::getMinBuyerRating() const {
    return minBuyerRating;
}

std::chrono::system_clock::time_point Item::getCreationTime() const {
    return creationTime;
}

void Item::setStartingBid(double newStartingBid) {
    startingBid = newStartingBid;
}

void Item::setBidIncrement(double newBidIncrement) {
    bidIncrement = newBidIncrement;
}
