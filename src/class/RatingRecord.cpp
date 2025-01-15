#include "class/RatingRecord.h"
#include <fstream>

// Serialization of a RatingRecord
void RatingRecord::serialize(std::ofstream& file) const {
    size_t raterIdLen = raterId.size();
    size_t rateeIdLen = rateeId.size();

    // Write string lengths and strings
    file.write(reinterpret_cast<const char*>(&raterIdLen), sizeof(raterIdLen));
    file.write(raterId.c_str(), raterIdLen);

    file.write(reinterpret_cast<const char*>(&rateeIdLen), sizeof(rateeIdLen));
    file.write(rateeId.c_str(), rateeIdLen);

    // Write numeric and boolean values
    file.write(reinterpret_cast<const char*>(&rating), sizeof(rating));
    file.write(reinterpret_cast<const char*>(&isBuyer), sizeof(isBuyer));
}

// Deserialization of a RatingRecord
RatingRecord RatingRecord::deserialize(std::ifstream& file) {
    RatingRecord record;
    size_t raterIdLen, rateeIdLen;

    // Read string lengths and strings
    if (!file.read(reinterpret_cast<char*>(&raterIdLen), sizeof(raterIdLen))) return {};
    record.raterId.resize(raterIdLen);
    file.read(record.raterId.data(), raterIdLen);

    if (!file.read(reinterpret_cast<char*>(&rateeIdLen), sizeof(rateeIdLen))) return {};
    record.rateeId.resize(rateeIdLen);
    file.read(record.rateeId.data(), rateeIdLen);

    // Read numeric and boolean values
    if (!file.read(reinterpret_cast<char*>(&record.rating), sizeof(record.rating))) return {};
    if (!file.read(reinterpret_cast<char*>(&record.isBuyer), sizeof(record.isBuyer))) return {};

    return record;
}
