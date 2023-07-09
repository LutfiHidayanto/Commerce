#pragma once   

#include "stdpch.h"
#include "categories.h"

class Product {
private:
    static int counter;
    std::string code;
    std::string name;
    double price;
    int quantity;
    std::string category;
    std::string owner;

public:
    Product(std::string name, double price, int quantity, std::string owner, std::string category);
    Product() {};
    std::string getCategory();
    void setCategory(std::string newCategory);
    std::string getCode();
    std::string getName();
    std::string getOwner();
    void setOwner(std::string owner);
    void setName(std::string newName);
    double getPrice();
    void setPrice(double newPrice);
    int getQuantity();
    void setQuantity(int newQuantity);
    std::string generateProductCode();
    void printProduct();
    std::map<std::string, Product*> searchByCategory(const std::map<std::string, Product*>& products, const std::string& category);
    void printByCategory(const std::map<std::string, Product*>& products, const std::string& category);
    nlohmann::json toJson();

};

