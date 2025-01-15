#include "../include/class/Authenticator.h"
#include "../include/controller/UserController.h"
#include "../include/dao/UserDataHandler.h"
#include "../include/ui/WelcomeScreen.h" 
#include "../include/ui/BidUI.h"
#include <iostream>

int main() {
     // Instantiate BidUI object
    // BidUI bidUI;
   // Authenticator authenticator;
   // authenticator.registerUser();
   std::string username = "admin1";
    std::string password = "admin123";
    std::string fullName = "Alice";
    std::string phoneNumber = "09012004";
    std::string email = "tha@example.com";
    std::string idType = "admin";
    std::string idNumber = "u-99998";

    User newUser(username, password, fullName, phoneNumber, email, idType, idNumber);
    
    // Save the user to file using UserDAO
    UserDataHandler userDAO;
    if (userDAO.saveUser(newUser)) {
        std::cout << "User created successfully.\n";
    } else {
        std::cout << "Failed to save user.\n";
    }
    WelcomeScreen WelcomeScreen;
    WelcomeScreen.displayMenu();
    // Call showBidMenu on the object
/*     std::string userId = "hai0901";  // Example user ID
    bidUI.showBidMenu(userId);  // Pass userId as argument */

     // Create a test user with hardcoded values
    

    // Now test authentication
    /* Authenticator authenticator;
    std::cout << "\nTesting authentication...\n";

    // Attempt to authenticate with hardcoded credentials
    if (authenticator.authenticate(username, password)) {
        std::cout << "Authentication successful. Logged in as " 
                  << authenticator.getLoggedUser()->getUsername() << "\n";
    } else {
        std::cout << "Authentication failed.\n";
    } 
    // Hardcoded users for testing
     UserController userController;
    WelcomeScreen welcomeScreen;
    welcomeScreen.displayMenu(); 
     */

    

    return 0; 
}
