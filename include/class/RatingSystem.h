#ifndef RATING_SYSTEM_H
#define RATING_SYSTEM_H

#include <string>
#include <unordered_map>
#include <vector>
//#include "RatingDataController.h"
#include "../controller/RatingDataController.h"
class RatingSystem {
private:
    RatingDataController dataController;

public:
    RatingSystem();
    ~RatingSystem();

    void addUser();
    void addRating();
    void getAverageRating() const;
    void displayAllUsers() const;
};

#endif // RATING_SYSTEM_H
