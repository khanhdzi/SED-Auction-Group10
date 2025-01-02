#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H
#include "../class/Authenticator.h"
class WelcomeScreen {
public:
    void displayWelcomeMessage();
    void displayMenu();
    void login();
private:
    Authenticator authenticator;  // Assuming you are using this for login
};


#endif // WELCOMESCREEN_H
