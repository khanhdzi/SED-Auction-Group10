#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    string username;
    string password;
    string fullName;
    string phoneNumber;
    string email;
    double credits;  // Add credits attribute

public:
    // Modify constructor to accept 6 arguments including credits
    User(string uname, string pass, string fname, string phone, string mail, double creds)
        : username(uname), password(pass), fullName(fname), phoneNumber(phone), email(mail), credits(creds) {}

    string getUsername() const { return username; }
    double getCredits() const { return credits; }
    void deductCredits(double amount) { credits -= amount; }

    // Optional: Add other getter and setter methods if needed
};

#endif
