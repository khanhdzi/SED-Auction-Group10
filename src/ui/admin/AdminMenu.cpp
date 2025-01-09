#include "../../../include/ui/admin/AdminMenu.h"
#include <iostream>

void AdminMenu::displayMenu() {
    std::cout << "=== Admin Menu ===\n";
    std::cout << "1. Manage Users\n";
    std::cout << "2. View Statistics\n";
    std::cout << "3. Logout\n";
    std::cout << "Enter your choice: ";
}

void AdminMenu::handleSelection(int choice) {
    switch (choice) {
        case 1:
          
            break;
        case 2:
          
            break;
        case 3:
            
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}


