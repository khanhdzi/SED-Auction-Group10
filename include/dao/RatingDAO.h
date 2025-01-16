#ifndef RATINGDAO_H
#define RATINGDAO_H

#include "../include/class/RatingRecord.h"
#include <string>
#include <vector>
#include <fstream>
#include <optional>



class RatingDAO {
private:
    static const std::string FILE_PATH; // File path for storing ratings
public:
    RatingDAO();

    // Add a new rating record
    bool saveRating(const RatingRecord& record);

    // Retrieve all ratings for a specific user
    std::vector<RatingRecord> getRatingsByUser(const std::string& userId, bool isBuyer);

    // Retrieve all ratings
    std::vector<RatingRecord> getAllRatings();
};

#endif // RATINGDAO_H
