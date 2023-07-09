#pragma once   

#include "product.h"

class Product;

class Categories
{
private:
    std::map<std::string, std::string> allCategories = {
        {"E", "Electronics"},
        {"F", "Fashion"},
        {"HK", "Home & Kitchen"},
        {"BPC", "Beauty & Personal Care"},
        {"B", "Books"},
        {"SO", "Sports & Outdoors"},
        {"HW", "Health & Wellness"},
        {"TG", "Toys & Games"},
        {"A", "Automotive"},
        {"OS", "Office Supplies"},
        {"G", "Groceries"},
        {"J", "Jewelry"},
        {"FU", "Furniture"},
        {"PS", "Pet Supplies"},
        {"BK", "Baby & Kids"},
        {"THI", "Tools & Home Improvement"},
        {"MM", "Music & Movies"},
        {"AC", "Arts & Crafts"},
        {"OG", "Outdoor & Garden"},
        {"FB", "Food & Beverages"},
    };
public:
    Categories() {};
    std::map<std::string, std::string> getAllCategories();
    bool isCategory(std::string category);
    void deleteCategory(std::string category);
    void printAllcategories();
    void setCategory(std::string newCategory, std::string code);
};

