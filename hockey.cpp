#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class HockeyPlayer {
private:
    std::string m_name;
    int m_id;
    std::string m_team;

public:
    HockeyPlayer(std::string name, int id, std::string team) 
        : m_name(name), m_id(id), m_team(team) {}

    std::string getName() const { return m_name; }

    int getId() const { return m_id; }

    std::string getTeam() const { return m_team; }
};

class LRUCache {
private:
    std::vector<HockeyPlayer> cache;
    const int cacheSize = 10;

public:
    HockeyPlayer* getPlayer(int playerId) {
        // Check if player is in the cache
        for (auto it = cache.begin(); it != cache.end(); ++it) {
            if (it->getId() == playerId) {
                // Move player to the front of the cache
                std::rotate(cache.begin(), it, it + 1);
                return &(*it); // Return pointer to found player
            }
        }

        // Player not found in cache, search in file
        std::ifstream file("hockeyplayers.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, team;
            int id;
            iss >> name >> id >> team;
            if (id == playerId) {
                // Add player to the front of the cache
                cache.insert(cache.begin(), HockeyPlayer(name, id, team));
                // If cache exceeds cacheSize, remove the last element
                if (cache.size() > cacheSize) {
                    cache.pop_back();
                }
                return &cache.front(); // Return pointer to found player
            }
        }

        // Player not found in cache or file
        return nullptr;
    }
};

int main() {
    // Test the getPlayer function
    LRUCache cache;
    int playerIdToSearch = 25; // For example, searching for player with ID 25
    HockeyPlayer* player = cache.getPlayer(playerIdToSearch);
    
    if (player != nullptr) {
        std::cout << "\n\n";
        std::cout << "***************" << std::endl;
        std::cout << "Player found: " << std::endl;
        std::cout << "Name: " << player->getName() << std::endl;
        std::cout << "ID: " << player->getId() << std::endl;
        std::cout << "Team: " << player->getTeam() << std::endl;
        std::cout << "***************" << std::endl;
        std::cout << "\n\n";
    } else {
        std::cout << "\n\n";
        std::cout << "***************" << std::endl;
        std::cout << "Player not found." << std::endl;
        std::cout << "***************" << std::endl;
        std::cout << "\n\n";
    }

    return 0;
}
