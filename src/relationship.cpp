#include "../header/relationship.h"

void Relationship::addFriend(const std::string& user1, const std::string& user2) {
    adjacencyList[user1].push_back(user2);
    adjacencyList[user2].push_back(user1);
}

void Relationship::deleteFriend(const std::string& user1, const std::string& user2) {
    auto it1 = std::find(adjacencyList[user1].begin(), adjacencyList[user1].end(), user2);
    auto it2 = std::find(adjacencyList[user2].begin(), adjacencyList[user2].end(), user1);

    if (it1 != adjacencyList[user1].end() && it2 != adjacencyList[user2].end()) {
        adjacencyList[user1].erase(it1);
        adjacencyList[user2].erase(it2);
        std::cout << user2 << " dihapus" << std::endl;
    } else {
        std::cout << "Tidak ada relasi dari " << user1 << " dan " << user2 << "." << std::endl;
    }
}

std::vector<std::string> Relationship::getFriends(const std::string& user) {
    std::vector<std::string> friends;

    if (adjacencyList.find(user) != adjacencyList.end()) {
        friends = adjacencyList[user];
    }

    return friends;
}

bool Relationship::areFriends(const std::string& user1, const std::string& user2) {
    auto it = std::find(adjacencyList[user1].begin(), adjacencyList[user1].end(), user2);

    if (it != adjacencyList[user1].end()) {
        return true;
    }

    return false;
}

const std::unordered_map<std::string, std::vector<std::string>>& Relationship::getAdjacencyList() const {
    return adjacencyList;
}

void Relationship::printFriends(const std::string& user) {
    if (adjacencyList.find(user) == adjacencyList.end()) {
        std::cout << "Ga ada teman dari " << user << std::endl;
        return;
    }

    std::cout << "Daftar teman dari " << user << ":" << std::endl;
    for (const std::string& friendName : adjacencyList[user]) {
        std::cout << friendName << std::endl;
    }
}