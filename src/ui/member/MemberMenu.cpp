#include "../../../include/ui/member/MemberMenu.h"
#include <iostream>

void MemberMenu::displayMenu() {
    std::cout << "=== Member Menu ===\n";
    std::cout << "1. View Profile\n";
    std::cout << "2. Edit Profile\n";
    std::cout << "3. Logout\n";
    std::cout << "Enter your choice: ";
}

void MemberMenu::handleSelection(int choice) {
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

