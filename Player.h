//
// Created by hborkows on 06.12.18.
//

#ifndef AAL_PLAYER_H
#define AAL_PLAYER_H

#include <vector>
#include <string>
#include <algorithm>

class Player
{
    std::string id;
    std::vector<Player> losingOpponents;
    std::vector<Player> winningOpponents;
    int strength;

public:
    Player() = default;
    Player(std::vector<Player> losingOpponents, std::vector<Player> winningOpponents, std::string id = std::string());

    bool operator<(const Player& other){return (this->strength) >= (other.strength);};
    Player& operator=(const Player& other);
    int getStrength() const {return strength;};
    int calculateStrength(){strength = winningOpponents.size() - losingOpponents.size();};
    void sortOpponents();
};


#endif //AAL_PLAYER_H
