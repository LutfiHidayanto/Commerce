#include "../header/user.h"


User::User(std::string name, std::string password, bool is_pembeli, double saldo) {
    this->name = name;
    this->password = password;
    this->is_pembeli = is_pembeli;
    this->saldo = saldo;
}

std::string User::getName() {
    return this->name;
}

void User::setName(std::string name) {
    this->name = name;
}

std::string User::getPassword() {
    return this->password;
}

void User::setPassword(std::string password) {
    this->password = password;
} 

bool User::getIs_pembeli() {
    return this->is_pembeli;
}

void User::setIs_pembeli(bool is_pembeli) {
    this->is_pembeli = is_pembeli;
}

double User::getSaldo() {
    return this->saldo;
}

void User::setSaldo(double saldo) {
    this->saldo = saldo;
}

nlohmann::json User::toJson() {
    nlohmann::json jsonData;
    jsonData["name"] = this->name;
    jsonData["password"] = this->password;
    jsonData["is_pembeli"] = this->is_pembeli;
    jsonData["saldo"] = this->saldo;
    return jsonData;
}