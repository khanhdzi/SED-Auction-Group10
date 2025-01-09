#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H
#include "../class/user.h"
#include "../class/Authenticator.h"
#include "../dao/userDataHandler.h"
class WelcomeScreen {
public:
    void displayWelcomeMessage();
    void displayMenu();
    void login();
private:
    Authenticator authenticator;  // Assuming you are using this for login
    static inline UserDataHandler userDAO;
    
  
};


#endif // WELCOMESCREEN_H
