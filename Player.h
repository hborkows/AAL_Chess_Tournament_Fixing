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
    Player(int id);
    Player(std::vector<Player*> losingOpponents, std::vector<Player*> winningOpponents, int id);

    bool operator<(const Player& other) {return (this->strength) >= (other.strength);};
    Player& operator=(const Player& other);

    void setUsed(const bool& flag) {used = flag;};
    bool isUsed() {return used;};
    bool noLosingOpponents();
    long getStrength() const {return strength;};
    int getId() const {return id;};
    std::vector<Player*> getLosingOpponents() {return losingOpponents;};
    void addLosingOpponent(Player* opponent);
    std::vector<Player*> getWinningOpponents() {return winningOpponents;};
    void addWinningOpponent(Player* opponent);
    int calculateStrength(){strength = winningOpponents.size() - losingOpponents.size();};
    void sortOpponents();
    void randomiseOpponents();
};

struct {
    bool operator()(Player* a, Player* b) const
    {
        return a->getWinningOpponents().size() < b->getWinningOpponents().size();
    }
} customWinningLess;

#endif //AAL_PLAYER_H
