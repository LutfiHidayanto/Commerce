#pragma once   
#include "stdpch.h"

class User
{
private:
    std::string name;
    std::string password;
    bool is_pembeli;
    double saldo;
    unsigned int id;
    static unsigned int nextId;
public:
    User(std::string name, std::string password, bool is_pembeli, double saldo);
    User() {};
    std::string getName();
    void setName(std::string name);
    std::string getPassword();
    void setPassword(std::string password);
    bool getIs_pembeli();
    void setIs_pembeli(bool is_pembeli);
    double getSaldo();
    void setSaldo(double saldo);
    nlohmann::json toJson();
};

