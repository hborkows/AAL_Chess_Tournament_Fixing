//
// Created by hborkows on 06.12.18.
//

#ifndef AAL_PLAYER_H
#define AAL_PLAYER_H

#include <vector>
#include <string>
#include <algorithm>
#include <functional>

class Player
{
    int id;
    bool used;
    std::vector<Player*> losingOpponents;
    std::vector<Player*> winningOpponents;
    long strength;

public:
    Player() = default;
    explicit Player(int id);

    bool operator<(const Player& other) {return (this->strength) >= (other.strength);};
    Player& operator=(const Player& other);

    void setUsed(const bool& flag) {used = flag;};
    bool isUsed() {return used;};
    bool noLosingOpponents();
    int getId() const {return id;};
    std::vector<Player*> getLosingOpponents() const {return losingOpponents;};
    void addLosingOpponent(Player* opponent);
    void addWinningOpponent(Player* opponent);
    void calculateStrength(){strength = winningOpponents.size() - losingOpponents.size();};
    void sortOpponents();
};

#endif //AAL_PLAYER_H
