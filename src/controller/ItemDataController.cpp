#include "../../include/controller/ItemDataController.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>

// Hàm tạo một item mới từ dữ liệu người dùng nhập và lưu vào file
void ItemDataController::createItemListing(std::string name, std::string category, std::string description, 
                                           double startingBid, double bidIncrement, std::chrono::system_clock::time_point endTime,
                                           int minBuyerRating) {

    // Tạo Item mới
    Item newItem(name, category, description, startingBid, bidIncrement, endTime, minBuyerRating);
    
    // Lưu thông tin vào file (ở đây chúng ta dùng file văn bản để lưu trữ)
    std::ofstream outFile("item_listings.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "Item: " << newItem.getName() << "\n";
        outFile << "Category: " << newItem.getCategory() << "\n";
        outFile << "Description: " << newItem.getDescription() << "\n";
        outFile << "Starting Bid: " << newItem.getStartingBid() << "\n";
        outFile << "Bid Increment: " << newItem.getBidIncrement() << "\n";
        outFile << "Min Buyer Rating: " << newItem.getMinBuyerRating() << "\n";
        std::time_t endTimeT = std::chrono::system_clock::to_time_t(endTime);
        outFile << "End Time: " << std::ctime(&endTimeT);
        outFile << "---------------------------------\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file for saving item listings.\n";
    }
}

// Hàm hiển thị tất cả các listings từ file
void ItemDataController::viewListings() const {
    std::ifstream inFile("item_listings.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << "\n";
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file to read item listings.\n";
    }
}
