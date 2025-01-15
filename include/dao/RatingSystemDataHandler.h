#ifndef RATING_SYSTEM_DATA_HANDLER_H
#define RATING_SYSTEM_DATA_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>
//#include "User.h"
#include "../class/user.h"
//add this
#include <unordered_map>

class RatingSystemDataHandler {
public:
    bool loadRatings(std::unordered_map<std::string, User>& users,
                     std::unordered_map<std::string, std::vector<int>>& buyerRatings,
                     std::unordered_map<std::string, std::vector<int>>& sellerRatings);

    void saveRatings(const std::unordered_map<std::string, User>& users,
                     const std::unordered_map<std::string, std::vector<int>>& buyerRatings,
                     const std::unordered_map<std::string, std::vector<int>>& sellerRatings) const;

    std::string joinRatings(const std::vector<int>& ratings) const;
};

#endif // RATING_SYSTEM_DATA_HANDLER_H
