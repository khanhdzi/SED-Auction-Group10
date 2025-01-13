// include/class/ItemDAO.h

#ifndef ITEMDAO_H
#define ITEMDAO_H

#include "../class/Item.h"
#include <vector>
#include <optional>

class ItemDAO {
public:
    ItemDAO();  // Constructor

    // Fetches all items
    std::vector<Item> getAllItems() const;

    // Finds an item by its ID
    std::optional<Item> findItemById(const std::string& itemId) const;

    // Add any other necessary methods for ItemDAO like adding, updating items, etc.
};

#endif
