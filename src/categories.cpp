#include "../header/categories.h"

Categories::Categories()
{ 
}

std::map<std::string, std::string> Categories::getAllCategories() {
    return this->allCategories;
}

void Categories::setCategory(std::string newCategory, std::string code) {
    allCategories[newCategory] = code;
}

void Categories::deleteCategory(std::string category) {
    allCategories.erase(category);
}