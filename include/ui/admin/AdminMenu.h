#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H

#include <string>

class AdminMenu {
public:
    void displayMenu();
    void handleSelection(int choice);

private:
    void manageUsersMenu(); // Manage Users Menu
    void statisticsMenu();
};

#endif // ADMIN_MENU_H
