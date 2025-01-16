#ifndef RATING_RECORD_H
#define RATING_RECORD_H

#include <string>
#include <fstream>

class RatingRecord {
public:
    std::string raterId;   // ID of the user providing the rating
    std::string rateeId;   // ID of the user receiving the rating
    double rating;         // Rating value (1 to 5)
    bool isBuyer;          // Whether the rating is for a buyer (true) or seller (false)

    // Default constructor
    RatingRecord() : raterId(""), rateeId(""), rating(0.0), isBuyer(false) {}

    // Parameterized constructor
    RatingRecord(const std::string& rater, const std::string& ratee, double rate, bool buyer)
        : raterId(rater), rateeId(ratee), rating(rate), isBuyer(buyer) {}

    // Serialization: Save the RatingRecord to a file
    void serialize(std::ofstream& file) const;

    // Deserialization: Load the RatingRecord from a file
    static RatingRecord deserialize(std::ifstream& file);
};

#endif // RATING_RECORD_H
