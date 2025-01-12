#include "../include/class/Authenticator.h"
#include "../include/controller/UserController.h"
#include "../include/dao/UserDataHandler.h"
#include "../include/ui/WelcomeScreen.h" 
#include "../include/ui/BidUI.h"
#include <iostream>

int main() {
    // Hardcoded users for testing
    UserController userController;
    WelcomeScreen welcomeScreen;
    welcomeScreen.displayMenu();
    // Instantiate BidUI object
    BidUI bidUI;
    
    // Call showBidMenu on the object
    std::string userId = "hai0901";  // Example user ID
    bidUI.showBidMenu(userId);  // Pass userId as argument


    

   /*  // Create a test user with hardcoded values
    std::string username = "hai0901";
    std::string password = "Hai09012004";
    std::string fullName = "haingx";
    std::string phoneNumber = "09012004";
    std::string email = "tha@example.com";
    std::string idType = "user";
    std::string idNumber = "99999";

    User newUser(username, password, fullName, phoneNumber, email, idType, idNumber);
    
    // Save the user to file using UserDAO
    UserDataHandler userDAO;
    if (userDAO.saveUser(newUser)) {
        std::cout << "User created successfully.\n";
    } else {
        std::cout << "Failed to save user.\n";
    }

    // Now test authentication
    Authenticator authenticator;
    std::cout << "\nTesting authentication...\n";

    // Attempt to authenticate with hardcoded credentials
    if (authenticator.authenticate(username, password)) {
        std::cout << "Authentication successful. Logged in as " 
                  << authenticator.getLoggedUser()->getUsername() << "\n";
    } else {
        std::cout << "Authentication failed.\n";
    } */

    return 0;
}
