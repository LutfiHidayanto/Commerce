#include "../header/product.h"

int Product::counter = 0;

Product::Product(std::string name, double price, int quantity, std::string owner, std::string category) {
    this->name = name;
    this->price = price;
    this->quantity = quantity;
    this->category = category;
    this->owner = owner;
    code = generateProductCode();
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

void Product::setOwner(std::string owner) {
    this->owner = owner;
}

void Product::setName(std::string newName) {
    this->name = newName;
}

double Product::getPrice() {
    return price;
}

void Product::setPrice(double newPrice) {
    price = newPrice;
}

int Product::getQuantity() {
    return this->quantity;
}

void Product::setQuantity(int newQuantity) {
    this->quantity = newQuantity;
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
void Product::printProduct() {
    std::cout <<  std::left <<  std::setw(10) << "KODE" << " | "<< std::left << std::setw(20) << "NAMA" << " | "
    << std::left << std::setw(11) << "HARGA" << " | " << "JUNLAH" << std::endl;

    std::cout << std::left << std::setw(10) << this->code << " | "
            << std::left << std::setw(20) << this->name << " | "
            << "Rp" << std::left << std::setw(6) << this->price << "000 | "
            << this->quantity << std::endl;
}

std::map<std::string, Product*> Product::searchByCategory(const std::map<std::string, Product*> & products, const std::string& category) {
    std::map<std::string, Product*> result;
    for (const auto& pair : products) {
        if (pair.second->getCategory() == category) {
            result.insert(pair);
        }
    }
    return result;
}

void Product::printByCategory(const std::map<std::string, Product*>& products, const std::string& category) {
    auto result = searchByCategory(products, category);
    if (result.empty()){
        std::cout << "Tidak ada produk dalam kategori ini!\n";
    } else {
        std::cout <<  std::left <<  std::setw(10) << "KODE" << " | "<< std::left << std::setw(20) << "NAMA" << " | "
            << std::left << std::setw(11) << "HARGA" << " | " << "JUNLAH" << std::endl;
        for (auto it = result.begin(); it != result.end(); ++it) {
            std::cout << std::left << std::setw(10) << it->first << " | "
                    << std::left << std::setw(20) << it->second->getName() << " | "
                    << "Rp" << std::left << std::setw(6) << it->second->getPrice() << "000 | "
                    << it->second->getQuantity() << std::endl;
        }
    }
}

nlohmann::json Product::toJson() {
    nlohmann::json jsonData;
    jsonData["code"] = code;
    jsonData["name"] = name;
    jsonData["price"] = price;
    jsonData["quantity"] = quantity;
    jsonData["owner"] = owner;
    jsonData["category"] = category;
    return jsonData;
}