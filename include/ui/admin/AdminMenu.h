#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H

#include <string>
#include "../../dao/ItemListingHandler.h"
class AdminMenu {
public:
    void displayMenu();
    void handleSelection(int choice);

private:
    ItemListingHandler itemDAO;
    void manageUsersMenu(); // Manage Users Menu
    void statisticsMenu();
};

#endif // ADMIN_MENU_H
