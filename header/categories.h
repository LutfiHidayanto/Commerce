#pragma once   

#include "../header/product.h"

class Product;

class Categories
{
private:
    std::map<std::string, std::pair<std::string, std::vector<Product*>>> allCategories = {
        {"E", {"Electronics", {}}},
        {"F", {"Fashion", {}}},
        {"HK", {"Home & Kitchen", {}}},
        {"BPC", {"Beauty & Personal Care", {}}},
        {"B", {"Books", {}}},
        {"SO", {"Sports & Outdoors", {}}},
        {"HW", {"Health & Wellness", {}}},
        {"TG", {"Toys & Games", {}}},
        {"A", {"Automotive", {}}},
        {"OS", {"Office Supplies", {}}},
        {"G", {"Groceries", {}}},
        {"J", {"Jewelry", {}}},
        {"F", {"Furniture", {}}},
        {"PS", {"Pet Supplies", {}}},
        {"BK", {"Baby & Kids", {}}},
        {"THI", {"Tools & Home Improvement", {}}},
        {"MM", {"Music & Movies", {}}},
        {"AC", {"Arts & Crafts", {}}},
        {"OG", {"Outdoor & Garden", {}}},
        {"FB", {"Food & Beverages", {}}},
    };
public:
    Categories() {};
    std::map<std::string, std::pair<std::string, std::vector<Product*>>> getAllCategories();
    void addProduct(std::string category,Product *product);
    bool isCategory(std::string category);
    void printAllcategories();
    bool printProductbyCategory(std::string categorycode);
    void setCategory(std::string newCategory, std::string code);
    void deleteCategory(std::string category);
    void deleteProduct(Product *product, std::string categorycode);
    void setQuantity(Product *product, std::string categorycode, int quantity); 
};

