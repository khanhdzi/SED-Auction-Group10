#ifndef CATEGORY_H
#define CATEGORY_H

#include <vector>
#include <string>
#include <fstream>

class Category {
public:
    static void addCategory(const std::string& category);
    static bool removeCategory(const std::string& category);
    static bool isValidCategory(const std::string& category);
    static void listCategories();
    
    // File Operations
    static void loadFromFile(const std::string& filePath);
    static void saveToFile(const std::string& filePath);

private:
    static std::vector<std::string> categories;
    static const std::string defaultFilePath;
};

#endif // CATEGORY_H
