#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip> // Dùng để định dạng thời gian
#include <fstream> // Dùng để làm việc với file
#include <algorithm> // Dùng cho remove_if
using namespace std;

// Lớp đại diện cho một mặt hàng
class ItemListing {
public:
    int id;
    string name;
    string category;
    string description;
    int startingBid;
    int bidIncrement;
    time_t endTime;
    int minBuyerRating;

    ItemListing(int itemId, string itemName, string cat, string desc, int startBid, int increment, time_t end, int minRating)
        : id(itemId), name(itemName), category(cat), description(desc), startingBid(startBid), 
          bidIncrement(increment), endTime(end), minBuyerRating(minRating) {}

    // Constructor mặc định để đọc từ file
    ItemListing() {}
};

// Lớp chính để quản lý danh sách mặt hàng
class ItemManager {
private:
    vector<ItemListing> listings; // Lưu trữ danh sách mặt hàng
    int itemIdCounter = 1;        // Biến tạo ID tự động cho mặt hàng mới
    const string filename = "listings.txt"; // Tên file lưu trữ dữ liệu

    bool isValidInput(int value) {
        return value > 0;
    }

    void saveToFile() {
        ofstream file(filename);
        if (!file) {
            cerr << "Error: Unable to open file for writing." << endl;
            return;
        }

        for (const auto& item : listings) {
            file << item.id << "|"
                 << item.name << "|"
                 << item.category << "|"
                 << item.description << "|"
                 << item.startingBid << "|"
                 << item.bidIncrement << "|"
                 << item.endTime << "|"
                 << item.minBuyerRating << endl;
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Unable to open file for reading. Starting with an empty list." << endl;
            return;
        }

        listings.clear();
        string line;
        while (getline(file, line)) {
            ItemListing item;
            size_t pos = 0;
            string token;

            pos = line.find('|');
            item.id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find('|');
            item.name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('|');
            item.category = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('|');
            item.description = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('|');
            item.startingBid = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find('|');
            item.bidIncrement = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find('|');
            item.endTime = stoll(line.substr(0, pos));
            line.erase(0, pos + 1);

            item.minBuyerRating = stoi(line);

            listings.push_back(item);
        }

        file.close();
    }

public:
    ItemManager() {
        loadFromFile();
    }

    // Thêm mặt hàng mới
    void createListing() {
        string name, category, description;
        int startingBid, bidIncrement, minBuyerRating, duration;
        
        cout << "\nInput information for the new item: \n";

        cout << "Product Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Category: ";
        getline(cin, category);

        cout << "Description: ";
        getline(cin, description);

        cout << "Starting Bid: ";
        cin >> startingBid;
        if (!isValidInput(startingBid)) {
            cout << "Invalid starting bid. Please enter a positive value.\n";
            return;
        }

        cout << "Bid Increment: ";
        cin >> bidIncrement;
        if (!isValidInput(bidIncrement)) {
            cout << "Invalid bid increment. Please enter a positive value.\n";
            return;
        }

        cout << "End Time (in hours from now): ";
        cin >> duration;
        if (!isValidInput(duration)) {
            cout << "Invalid duration. Please enter a positive value.\n";
            return;
        }

        cout << "Min Buyer Rating: ";
        cin >> minBuyerRating;
        if (!isValidInput(minBuyerRating)) {
            cout << "Invalid buyer rating. Please enter a positive value.\n";
            return;
        }

        ItemListing newItem(
            itemIdCounter,
            name,
            category,
            description,
            startingBid,
            bidIncrement,
            time(nullptr) + duration * 3600, // Thời gian kết thúc tính theo giây
            minBuyerRating
        );

        listings.push_back(newItem);
        saveToFile();
        cout << "New item registered with ID: " << itemIdCounter << endl;
        itemIdCounter++;
    }

    // Hiển thị danh sách mặt hàng
    void viewListings() {
        loadFromFile();

        if (listings.empty()) {
            cout << "\nThere are no items in the list.\n";
            return;
        }

        cout << "\nCurrent Item List:\n";
        for (auto& item : listings) {
            cout << "ID: " << item.id << endl;
            cout << "Item Name: " << item.name << endl;
            cout << "Category: " << item.category << endl;
            cout << "Short Description: " << item.description << endl;
            cout << "Starting Bid: " << item.startingBid << endl;
            cout << "Bid Increment: " << item.bidIncrement << endl;
            cout << "End Time: " << put_time(localtime(&item.endTime), "%Y-%m-%d %H:%M:%S") << endl;
            cout << "Min Buyer Rating: " << item.minBuyerRating << endl;
            cout << "-------------------------------------\n";
        }
    }

    // Xóa mặt hàng theo ID
    void deleteListing(int itemId) {
        auto it = remove_if(listings.begin(), listings.end(), [&](ItemListing& item) {
            return item.id == itemId;
        });

        if (it != listings.end()) {
            listings.erase(it, listings.end());
            saveToFile();
            cout << "Item with ID " << itemId << " deleted.\n";
        } else {
            cout << "No item found with ID " << itemId << ".\n";
        }
    }

    // Cập nhật mặt hàng
    void updateListing(int itemId) {
        for (auto& item : listings) {
            if (item.id == itemId) {
                cout << "Updating Item ID " << itemId << endl;
                cout << "New Name: ";
                cin.ignore();
                getline(cin, item.name);
                cout << "New Category: ";
                getline(cin, item.category);
                cout << "New Starting Bid: ";
                cin >> item.startingBid;
                saveToFile();
                cout << "Update successful!\n";
                return;
            }
        }
        cout << "No item found with ID " << itemId << ".\n";
    }
};

int main() {
    ItemManager manager;
    int choice = 0;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. New Item\n";
        cout << "2. View Listings\n";
        cout << "3. Delete Item\n";
        cout << "4. Update Item\n";
        cout << "5. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.createListing();
                break;
            case 2:
                manager.viewListings();
                break;
            case 3: {
                int deleteId;
                cout << "Enter ID to delete: ";
                cin >> deleteId;
                manager.deleteListing(deleteId);
                break;
            }
            case 4: {
                int updateId;
                cout << "Enter ID to update: ";
                cin >> updateId;
                manager.updateListing(updateId);
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
