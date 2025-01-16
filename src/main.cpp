#include "../include/class/Authenticator.h"
#include "../include/controller/UserController.h"
#include "../include/dao/UserDataHandler.h"
#include "../include/ui/WelcomeScreen.h" 
#include "../include/controller/ItemDataController.h"
#include "../include/utils/Category.h"
#include "../include/ui/BidUI.h"
#include <iostream>

int main() {
     // Instantiate BidUI object
    // BidUI bidUI;
   // Authenticator authenticator;
   // authenticator.registerUser();
  /*  std::string username = "admin1";

    std::string password = "admin123";
    std::string fullName = "Alice";
    std::string phoneNumber = "09012004";
    std::string email = "tha@example.com";
    std::string idType = "admin";
    std::string idNumber = "u-99998";

    User newUser(username, password, fullName, phoneNumber, email, idType, idNumber);
     UserDataHandler userDAO;
    if (userDAO.saveUser(newUser)) {
        std::cout << "User created successfully.\n";
    } else {
        std::cout << "Failed to save user.\n";
    }
    WelcomeScreen WelcomeScreen;
    WelcomeScreen.displayMenu();
     */

    

 // Initialize controllers
    ItemDataController itemController;

    // Load categories
    std::cout << "Loading categories...\n";
    Category::loadFromFile("data/categories.dat");
    Category::listCategories();

    // Create item
    std::cout << "Creating a test item...\n";
    std::string name = "Test Item";
    std::string category = "Electronics";
    std::string description = "A test description.";
    double startingBid = 100.0;
    double bidIncrement = 10.0;
    auto endTime = std::chrono::system_clock::now() + std::chrono::hours(24);

    itemController.createItemListing(name, category, description, startingBid, bidIncrement, endTime);

    // Save items
    std::cout << "Saving items to file...\n";
    itemController.saveListingsToFile("data/items.dat");

    // Verify items in file
    std::cout << "Reloading items from file...\n";
    itemController.loadListingsFromFile("data/items.dat");
    itemController.viewListings();


   

 
   
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
