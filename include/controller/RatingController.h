#ifndef RATINGCONTROLLER_H
#define RATINGCONTROLLER_H

#include "../dao/UserDataHandler.h"
#include <string>

class RatingController {
private:
    UserDataHandler userDAO;

public:
    void rateUser(const std::string& raterId, const std::string& rateeId, double rating, bool isBuyer);
    void viewUserRatings(const std::string& userId);
    void updateUserRatings(const std::string& rateeId, double rating, bool isBuyer);

};


#endif
