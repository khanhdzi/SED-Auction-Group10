// include/ui/BidUI.h
#ifndef BID_UI_H
#define BID_UI_H

#include "../controller/BidController.h"

class BidUI {
public:
    void showBidMenu();
    void processBidInput();
    void displayBidHistory(const std::string& itemId);
    
private:
    BidController bidController;
};

#endif