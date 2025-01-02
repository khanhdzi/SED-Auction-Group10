#include <iostream>
#include <limits>  

#include "../../include/ui/WelcomeScreen.h"
#include "../../include/controller/UserController.h"
#include "../../include/class/Authenticator.h"
#include "../../include/utils/InputValidator.h"
/* #include "../../include/ui/guest/GuestMenu.h"   
#include "../../include/ui/member/MemberMenu.h" 
#include "../../include/ui/admin/AdminMenu.h"  */  
UserController userController;
void WelcomeScreen::displayWelcomeMessage() {
    std::cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n";
    std::cout << "Semester 3 2024\n";
    std::cout << "AUCTION APPLICATION\n";
    std::cout << "Instructor: Dr Ling Huo Chong\n";
    std::cout << "Group: Group No.\n";
    std::cout << "XXXXXXX, Student Name\n";
    std::cout << "XXXXXXX, Student Name\n";
    std::cout << "XXXXXXX, Student Name\n";
    std::cout << "XXXXXXX, Student Name\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "Use the app as:\n";
    std::cout << "1. Guest\n";
    std::cout << "2. Member\n";
    std::cout << "3. Admin\n";
    std::cout << "Enter your choice: ";
}

void WelcomeScreen::displayMenu() {
    int choice;
    displayWelcomeMessage();
    std::cin >> choice;
    
    // Clear the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1:
            {
               
                break;
            }
        case 2:
            {
                login();
                break;
            }
        case 3:
            {
                login();
                break;
            }
        default:
            std::cout << "Invalid choice, please try again.\n";
            displayMenu();  // Re-run the welcome screen on invalid input
            break;
    }
}

void WelcomeScreen::login() {
    std::string username = InputValidator::validateString("Enter username: ");
    std::string password = InputValidator::validatePassword("Enter password: ");
    
    if (authenticator.authenticate(username, password)) {
        std::cout << "Login successful.\n";
        // Proceed to the next screen based on the role (Manager, Employee, etc.)
    } else {
        std::cout << "Invalid username or password.\n";
    }
}
