#include "../../include/controller/RatingController.h"
#include "../../include/dao/RatingDAO.h"
#include <iostream>

void RatingController::rateUser(const std::string& raterId, const std::string& rateeId, double rating, bool isBuyer) {
    UserDataHandler userHandler;

    auto users = userHandler.getAllUsers();
    auto usernameExists = [&users](const std::string& username) {
        for (const auto& user : users) {
            if (user.getUsername() == username) {
                return true;
            }
        }
        return false;
    };

    if (!usernameExists(raterId)) {
        std::cerr << "Rater ID not found.\n";
        return;
    }
    if (!usernameExists(rateeId)) {
        std::cerr << "Ratee ID not found.\n";
        return;
    }

    if (rating < 1 || rating > 5) {
        std::cerr << "Rating must be between 1 and 5.\n";
        return;
    }

    RatingDAO ratingDAO;
    RatingRecord record = {raterId, rateeId, rating, isBuyer};
    if (ratingDAO.saveRating(record)) {
        std::cout << "Rating submitted successfully!\n";

        // Update user's average ratings
        for (auto& user : users) {
            if (user.getUsername() == rateeId) {
                // Calculate average rating
                double total = 0.0;
                int count = 0;

                auto ratings = ratingDAO.getRatingsByUser(rateeId, isBuyer);
                for (const auto& rec : ratings) {
                    total += rec.rating;
                    count++;
                }

                // Update the respective rating
                if (isBuyer) {
                    user.setBuyerRating(count > 0 ? total / count : 0.0);
                } else {
                    user.setSellerRating(count > 0 ? total / count : 0.0);
                }

                // Save updated user
                if (userHandler.updateUser(user)) {
                    std::cout << "User ratings updated successfully.\n";
                } else {
                    std::cerr << "Failed to save updated user ratings.\n";
                }
                break;
            }
        }
    } else {
        std::cerr << "Failed to save the rating.\n";
    }
}




void RatingController::viewUserRatings(const std::string& userId) {
    RatingDAO ratingDAO;

    // Retrieve buyer and seller ratings
    std::vector<RatingRecord> buyerRatings = ratingDAO.getRatingsByUser(userId, true);
    std::vector<RatingRecord> sellerRatings = ratingDAO.getRatingsByUser(userId, false);

    // Calculate average ratings
    double buyerAverage = 0.0, sellerAverage = 0.0;
    if (!buyerRatings.empty()) {
        for (const auto& record : buyerRatings) {
            buyerAverage += record.rating;
        }
        buyerAverage /= buyerRatings.size();
    }
    if (!sellerRatings.empty()) {
        for (const auto& record : sellerRatings) {
            sellerAverage += record.rating;
        }
        sellerAverage /= sellerRatings.size();
    }

    // Display ratings
    std::cout << "Ratings for User: " << userId << "\n";

    std::cout << "As Buyer (Average: " << buyerAverage << "):\n";
    for (const auto& record : buyerRatings) {
        std::cout << "Rater: " << record.raterId << ", Rating: " << record.rating << "\n";
    }

    std::cout << "As Seller (Average: " << sellerAverage << "):\n";
    for (const auto& record : sellerRatings) {
        std::cout << "Rater: " << record.raterId << ", Rating: " << record.rating << "\n";
    }
}
void RatingController::updateUserRatings(const std::string& rateeId, double rating, bool isBuyer) {
    auto users = userDAO.getAllUsers();
    for (auto& user : users) {
        if (user.getUsername() == rateeId) {
            if (isBuyer) {
                user.addBuyerRating(rating);
            } else {
                user.addSellerRating(rating);
            }
            userDAO.updateUser(user);
            std::cout << "Updated user ratings successfully.\n";
            return;
        }
    }
    std::cerr << "User not found.\n";
}
