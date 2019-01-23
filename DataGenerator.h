//
// Created by hborkows on 07.12.18.
//

#ifndef AAL_DATAGENERATOR_H
#define AAL_DATAGENERATOR_H

#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>
#include "Player.h"

struct Pair
{
    int left;
    int right;
    bool result;

    Pair(int l, int r): left(l), right(r), result() {};
    Pair(int l, int r, bool result): left(l), right(r), result(result) {};
};

class DataGenerator
{
    int playerCount;
    int winningPlayer;
    Player* winPlayer;
    std::vector<Pair> matchUps;

public:
    DataGenerator(size_t n, int winningPlayer);
    ~DataGenerator() = default;

    Player* getWinningPlayer() const;
    std::vector<Player*> generatePlayers();
    std::vector<Player*> generatePlayersNotRand(std::vector<Pair> matchUps);
    int getPlayerCount() {return playerCount;};
    std::vector<Pair> getMatchUps() { return matchUps;};
};


#endif //AAL_DATAGENERATOR_H
