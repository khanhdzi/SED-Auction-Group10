#include <iostream>
#include <limits>  

#include "../../include/ui/WelcomeScreen.h"
#include "../../include/controller/UserController.h"
#include "../../include/class/Authenticator.h"
#include "../../include/utils/InputValidator.h"
#include "../../include/ui/guest/GuestMenu.h"   
#include "../../include/ui/member/MemberMenu.h" 
#include "../../include/ui/admin/AdminMenu.h"  

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
                authenticator.Userlogin();
                if (authenticator.isLoggedIn()) {
                    User* loggedUser = authenticator.getLoggedUser();
                    if (loggedUser->getIdType() == "member") { // Check if user is a member
                        MemberMenu memberMenu;
                        memberMenu.displayMenu();
                    } else {
                        std::cout << "Access denied: Only members can log in here.\n";
                    }
                }
                break;
            }
        case 3:
            {
                authenticator.Userlogin();
                if (authenticator.isLoggedIn()) {
                    User* loggedUser = authenticator.getLoggedUser();
                    if (loggedUser->getIdType() == "admin") { // Check if user is an admin
                        AdminMenu adminMenu;
                        adminMenu.displayMenu();
                    } else {
                        std::cout << "Access denied: Only admins can log in here.\n";
                    }
                }
                break;
            }
        default:
            std::cout << "Invalid choice, please try again.\n";
            displayMenu();  // Re-run the welcome screen on invalid input
            break;
    }
}


