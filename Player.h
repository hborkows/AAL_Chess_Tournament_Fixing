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
    bool used;
    std::vector<Player*> losingOpponents;
    std::vector<Player*> winningOpponents;
    long strength;

public:
    Player() = default;
    Player(std::vector<Player*> losingOpponents, std::vector<Player*> winningOpponents, std::string id = std::string());

    bool operator<(const Player& other) {return (this->strength) >= (other.strength);};
    Player& operator=(const Player& other);

    void setUsed(const bool& flag) {used = flag;};
    bool isUsed() {return used;};
    bool noLosingOpponents();
    long getStrength() const {return strength;};
    std::vector<Player*> getLosingOpponents() {return losingOpponents;};
    std::vector<Player*> getWinningOpponents() {return winningOpponents;};
    int calculateStrength(){strength = winningOpponents.size() - losingOpponents.size();};
    void sortOpponents();
    void randomiseOpponents();
};


#endif //AAL_PLAYER_H
