#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class HockeyPlayer {
private:
    std::string name;
    int id;
    std::string team;

public:
    HockeyPlayer(std::string playerName, int playerId, std::string playerTeam) 
        : name(playerName), id(playerId), team(playerTeam) {}

    std::string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    std::string getTeam() const {
        return team;
    }
};

class FileHandler {
public:
    static HockeyPlayer searchPlayer(int playerId) {
        std::ifstream file("hockeyplayers.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, team;
            int id;
            iss >> name >> id >> team;
            if (id == playerId) {
                return HockeyPlayer(name, id, team);
            }
        }
        // Return a default-constructed HockeyPlayer if player not found
        return HockeyPlayer("", -1, "");
    }
};

int main() {
    // Test the searchPlayer function
    int playerIdToSearch = 57; // For example, searching for player with ID 25
    HockeyPlayer player = FileHandler::searchPlayer(playerIdToSearch);
    
    // Check if player found
    if (player.getId() != -1) {
        std::cout << "Player found:\n";
        std::cout << "Name: " << player.getName() << "\n";
        std::cout << "ID: " << player.getId() << "\n";
        std::cout << "Team: " << player.getTeam() << "\n";
    } else {
        std::cout << "Player not found.\n";
    }

    return 0;
}
