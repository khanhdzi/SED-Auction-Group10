#include "../../include/dao/RatingDAO.h"
#include "../../include/class/RatingRecord.h"
#include <iostream>
#include <sstream>
#include <filesystem>

// Initialize the file path
const std::string RatingDAO::FILE_PATH = "data/ratings.dat";

// Constructor
RatingDAO::RatingDAO() {
    // Ensure the "data" directory exists
    if (!std::filesystem::exists("data")) {
        std::filesystem::create_directory("data");
    }
}

// Add a new rating record
bool RatingDAO::saveRating(const RatingRecord& record) {
    std::ofstream file(FILE_PATH, std::ios::binary | std::ios::app); // Binary append mode
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << FILE_PATH << "\n";
        return false;
    }
    record.serialize(file); // Serialize the record into the binary file
    file.close();
    return true;
}

// Retrieve all ratings for a specific user
std::vector<RatingRecord> RatingDAO::getRatingsByUser(const std::string& userId, bool isBuyer) {
    std::ifstream file(FILE_PATH, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << FILE_PATH << "\n";
        return {};
    }

    std::vector<RatingRecord> result;
    while (true) {
        RatingRecord record = RatingRecord::deserialize(file);
        if (file.eof() || file.fail()) break; // Stop if the end of file is reached or failure occurs
        if (record.rateeId == userId && record.isBuyer == isBuyer) {
            result.push_back(record);
        }
    }
    file.close();
    return result;
}

// Retrieve all ratings
std::vector<RatingRecord> RatingDAO::getAllRatings() {
    std::ifstream file(FILE_PATH, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << FILE_PATH << "\n";
        return {};
    }

    std::vector<RatingRecord> result;
    while (true) {
        RatingRecord record = RatingRecord::deserialize(file);
        if (file.eof() || file.fail()) break; // Stop if the end of file is reached or failure occurs
        result.push_back(record);
    }
    file.close();
    return result;
}
