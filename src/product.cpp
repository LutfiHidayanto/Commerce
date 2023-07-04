#include "../header/product.h"

int Product::counter = 0;

Product::Product(std::string name, double price, int quantity, std::string owner, std::string category) {
    code = generateProductCode();
    this->name = name;
    this->price = price;
    this->quantity = quantity;
    this->category = category;
}

std::string Product::getCategory() {
    return category;
}

void Product::setCategory(std::string newCategory) {
    category = newCategory;
}

std::string Product::getCode() {
    return code;
}

std::string Product::getName() {
    return name;
}

std::string Product::getOwner() {
    return owner;
}

std::string Product::setOwner(std::string owner) {
    this->owner = owner;
}

void Product::setName(std::string newName) {
    name = newName;
}

double Product::getPrice() {
    return price;
}

void Product::setPrice(double newPrice) {
    price = newPrice;
}

int Product::getQuantity() {
    return quantity;
}

void Product::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

std::string Product::generateProductCode() {
    counter++;
    std::string prefix = this->category;
    std::string paddedCounter = std::to_string(counter);
    int leadingZeros = 4 - paddedCounter.length();
    if (leadingZeros > 0) {
        paddedCounter = std::string(leadingZeros, '0') + paddedCounter;
    }
    return prefix + paddedCounter;
}

void Product::display() {
    std::cout << "Product Code: " << this->code << std::endl;
    std::cout << "Product Name: " << this->name << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
}
