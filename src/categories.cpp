#include "../header/categories.h"
#include "stdpch.cpp"


std::map<std::string, std::string> Categories::getAllCategories() {
    return this->allCategories;
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
        std::cout << std::left <<  std::setw(25) << pair.first << " | "<< std::left << std::setw(20) << pair.second << std::endl;;
    }
}

