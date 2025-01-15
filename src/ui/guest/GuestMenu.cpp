#include "../../../include/ui/guest/GuestMenu.h"
#include "../../../include/ui/WelcomeScreen.h"
#include <iostream>
#include <limits>
#include "../../../include/utils/utils.h"
#include "../../../include/class/Authenticator.h"

void GuestMenu::displayMenu() {
    int choice;
    do {
        std::cout << "=== Guest Menu ===\n";
        std::cout << "1. Browse Catalog\n";
        std::cout << "2. Sign Up\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Validate input and clear invalid input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        handleSelection(choice);

    } while (choice != 3); // Exit when the user selects option 3
}

void GuestMenu::handleSelection(int choice) {
    Utils::clearScreen();
    switch (choice) {
        case 1:
        
            break;
        case 2:
            {  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Authenticator authenticator;
                authenticator.registerUser();
                Utils::printSeparatorLine();
                std::cout << "Redirecting to the Welcome Screen...\n";
                WelcomeScreen welcomeScreen;
                welcomeScreen.displayMenu();
                return;
            }
        case 3:
            std::cout << "Thank you for visiting.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}
