// main.cpp
#include "RatingSystem.h"
using namespace std;

int main() {
    RatingSystem rs;

    char choice;
    while (true) {
        menu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case '1':
            rs.displayAllUsers();
            break;
        case '2':
            rs.addUser();
            break;
        case '3':
            rs.addRating();
            break;
        case '4':
            rs.getAverageRating();
            break;
        case '5':
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
