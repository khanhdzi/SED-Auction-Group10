#include <iostream>
#include "../include/dao/ItemListingHandler.h"
#include "../include/controller/ItemDataController.h"
#include "../include/ui/member/MemberMenu.h"
#include "../include/utils/utils.h"

int main() {
    // Initialize DAO and Controller
    ItemListingHandler itemDAO;
    ItemDataController itemController;

    // Test DAO: Fetch and Display Items
    std::cout << "=== Testing Item DAO ===\n";
    auto itemsFromDAO = itemDAO.getAllItems();
    if (itemsFromDAO.empty()) {
        std::cout << "No items found using DAO.\n";
    } else {
        itemDAO.displayItems(itemsFromDAO);
    }

    // Test Controller: Fetch and Display Items
    std::cout << "\n=== Testing Item Controller ===\n";
    std::cout << "Calling viewAllItems() from ItemDataController:\n";
    itemController.viewAllItems();

    // Test Member Menu
    std::cout << "\n=== Opening Member Menu ===\n";
    MemberMenu memberMenu;
    memberMenu.displayMenu();

    return 0;
}
