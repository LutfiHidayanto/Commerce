#include "../header/categories.h"
#include "stdpch.cpp"


std::map<std::string, std::pair<std::string, std::vector<Product*>>> Categories::getAllCategories() {
    return this->allCategories;
}

void Categories::addProduct(std::string categorycode, Product *product) {
    if (!isCategory(categorycode)) {
        std::cout << "Kategori tidak valid" << std::endl;
        return;
    }
    allCategories[categorycode].second.push_back(product);
}
bool Categories::isCategory(std::string categorycode) {
    if (allCategories.count(categorycode) != 0) {
        return true;
    }
    return false;
}
void Categories::setCategory(std::string newCategory, std::string code) {
    allCategories[code] = {newCategory, {}};
}

void Categories::deleteCategory(std::string category) {
    allCategories.erase(category);
}

void Categories::printAllcategories() {
    std::cout <<  std::left <<  std::setw(25) << "KODE" << " | "<< std::left << std::setw(20) << "NAMA" << std::endl;
    for (const auto& pair : allCategories) {
        std::cout << std::left <<  std::setw(25) << pair.second.first << " | "<< std::left << std::setw(20) << pair.first << std::endl;;
    }
}

bool Categories::printProductbyCategory(std::string categorycode) {
    if (!isCategory(categorycode)) return false;
    std::vector<Product*> fiilteredProducts = allCategories[categorycode].second;

    if (fiilteredProducts.empty()) {
        std::cout << "TIDAK ADA PRODUK DALAM KATEGORY INI";
        return false;
    } else {
        std::cout <<  std::left <<  std::setw(10) << "KODE" << " | "<< std::left << std::setw(20) << "NAMA" << " | "<< std::left << std::setw(11
        ) << "HARGA" << " | " << "JUNLAH" << std::endl;
        for (auto i : fiilteredProducts) {
            std::cout << std::left << std::setw(10) << i->getCode() << " | "
                    << std::left << std::setw(20) << i->getName() << " | "
                    << "Rp" << std::left << std::setw(6) << i->getPrice() << "000 | "
                    << i->getQuantity() << std::endl;
        }
        return true;
    }

}

void Categories::deleteProduct(Product *product, std::string categorycode) {
    if (!isCategory(categorycode)) return;

    auto it = std::find(allCategories[categorycode].second.begin(), allCategories[categorycode].second.end(), product);

    // Check if the element was found
    if (it != allCategories[categorycode].second.end()) {
        // Erase the element
        allCategories[categorycode].second.erase(it);
    } else {
        std::cout << "Element not found." << std::endl;
    }
}
void Categories::setQuantity(Product *product, std::string categorycode, int quantity) {
    if (!isCategory(categorycode)) return;
    
    auto it = std::find(allCategories[categorycode].second.begin(), allCategories[categorycode].second.end(), product);

    // Iterate over the map
    for (auto& categoryPair : allCategories) {
        // Access the vector of Product* objects
        std::vector<Product*>& products = categoryPair.second.second;

        // Iterate over the vector of Product* objects
        for (Product* product : products) {
            // Dereference the Product* pointer and decrement the quantity
            product->setQuantity(quantity);
        }
    }
}