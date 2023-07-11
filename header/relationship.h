#pragma once

#include "stdpch.h"

class Relationship {
private:
    std::unordered_map<std::string, std::set<std::string>> adjacencyList;
public:
    void addFriend(const std::string& user1, const std::string& user2);
    void deleteFriend(const std::string& user1, const std::string& user2);
    std::set<std::string> getFriends(const std::string& user);
    bool areFriends(const std::string& user1, const std::string& user2);
    const std::unordered_map<std::string, std::set<std::string>>& getAdjacencyList() const;
    void printFriends(const std::string& user);
};  

