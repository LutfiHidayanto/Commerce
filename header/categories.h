#pragma once   

#include <map>
#include <string>

class Categories
{
private:
    std::map<std::string, std::string> allCategories = {
        {"Electronics", "E"},
        {"Fashion", "F"},
        {"Home & Kitchen", "HK"},
        {"Beauty & Personal Care", "BPC"},
        {"Books", "B"},
        {"Sports & Outdoors", "SO"},
        {"Health & Wellness", "HW"},
        {"Toys & Games", "TG"},
        {"Automotive", "A"},
        {"Office Supplies", "OS"},
        {"Groceries", "G"},
        {"Jewelry", "J"},
        {"Furniture", "F"},
        {"Pet Supplies", "PS"},
        {"Baby & Kids", "BK"},
        {"Tools & Home Improvement", "THI"},
        {"Music & Movies", "MM"},
        {"Arts & Crafts", "AC"},
        {"Outdoor & Garden", "OG"},
        {"Food & Beverages", "FB"}
    };
public:
    Categories() {};
    std::map<std::string, std::string> getAllCategories();
    void setCategory(std::string newCategory, std::string code);
    void deleteCategory(std::string category);
};

