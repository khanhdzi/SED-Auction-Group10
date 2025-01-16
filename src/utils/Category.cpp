#include "../../include/utils/Category.h"
#include <algorithm>
#include <iostream>
#include <filesystem>

std::vector<std::string> Category::categories = {};
const std::string Category::defaultFilePath = "data/categories.dat";

// Add a new category
void Category::addCategory(const std::string& category) {
    if (!isValidCategory(category)) {
        categories.push_back(category);
        std::cout << "Category added successfully.\n";
    } else {
        std::cout << "Category already exists.\n";
    }
}

// Remove an existing category
bool Category::removeCategory(const std::string& category) {
    auto it = std::find(categories.begin(), categories.end(), category);
    if (it != categories.end()) {
        categories.erase(it);
        std::cout << "Category removed successfully.\n";
        return true;
    } else {
        std::cout << "Category not found.\n";
        return false;
    }
}

// Check if a category is valid
bool Category::isValidCategory(const std::string& category) {
    return std::find(categories.begin(), categories.end(), category) != categories.end();
}

// List all categories
void Category::listCategories() {
    if (categories.empty()) {
        std::cout << "No categories available.\n";
        return;
    }

    std::cout << "Available Categories:\n";
    for (const auto& category : categories) {
        std::cout << "- " << category << "\n";
    }
}


// Load categories from a file
// Load categories from a file
void Category::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open category file for loading.\n";
        return;
    }

    // Clear existing categories to avoid duplicates
    categories.clear();

    std::string category;
    while (std::getline(file, category)) {
        if (!category.empty()) {
            categories.push_back(category);
        }
    }

    file.close();
    std::cout << "Categories loaded successfully from " << filePath << ".\n";
}


// Save categories to a file
void Category::saveToFile(const std::string& filePath) {
    // Ensure the directory exists
    std::filesystem::create_directories("data");

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open category file for saving.\n";
        return;
    }

    for (const auto& category : categories) {
        file << category << "\n";
    }

    file.close();
    std::cout << "Categories saved successfully to " << filePath << ".\n";
}

void Category::displayCategories() {
    std::cout << "=====================================\n";
    std::cout << "        Loading Categories...        \n";
    std::cout << "=====================================\n";
    
    // Load categories from file
    Category::loadFromFile("data/categories.dat");

    // Display the loaded categories
    std::cout << "\nAvailable Categories:\n";
    std::cout << "-------------------------------------\n";
    
    // Check if categories exist and display them
    if (Category::categories.empty()) {
        std::cout << "No categories available.\n";
    } else {
        int index = 1;
        for (const auto& category : Category::categories) {
            std::cout << index++ << ". " << category << "\n";
        }
    }

    std::cout << "=====================================\n";
}