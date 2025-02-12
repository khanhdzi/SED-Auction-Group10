#ifndef MEMBER_MENU_H
#define MEMBER_MENU_H

#include "../../class/Authenticator.h"
#include "../../dao/ItemListingHandler.h"
#include "../../../include/controller/BidController.h"
#include "../../../include/controller/ItemDataController.h"
#include "../../../include/utils/InputValidator.h"
#include <string>

// Forward declaration to avoid circular dependency
class UserController;

class MemberMenu {
public:
    void displayMenu();
    void handleSelection(int choice);
    void displayDashboard();

    // Submenus
    void displayGeneralFeaturesMenu();
    void displayBuyerFeaturesMenu();
    void displaySellerFeaturesMenu();

    // General features
    void viewProfile(UserController& userController); // Correctly declared
    void editProfile(UserController& userController);

    // Buyer-specific features


    // Seller-specific features


private:
    Authenticator authenticator; // To manage authentication if needed
    ItemListingHandler ItemDAO;
};

#endif // MEMBER_MENU_H
