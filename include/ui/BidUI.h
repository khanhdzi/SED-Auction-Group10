#ifndef BID_UI_H
#define BID_UI_H

#include "../controller/BidController.h"
#include <string>

class BidUI {
public:
    void showBidMenu(const std::string& userId);
    void searchItems(const std::string& userId);
    void placeBid(const std::string& userId);

private:
    BidController bidController;
};

#endif
