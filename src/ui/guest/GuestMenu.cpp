#include "../../../include/ui/guest/GuestMenu.h"
#include <iostream>

void GuestMenu::displayMenu() {
    std::cout << "=== Guest Menu ===\n";
    std::cout << "1. Browse Catalog\n";
    std::cout << "2. Sign Up\n";
    std::cout << "3. Logout\n";
    std::cout << "Enter your choice: ";
}

void GuestMenu::handleSelection(int choice) {
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

