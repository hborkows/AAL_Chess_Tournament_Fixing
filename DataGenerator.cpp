//
// Created by hborkows on 07.12.18.
//

#include "DataGenerator.h"

DataGenerator::DataGenerator(size_t n, int winningPlayer)
{
    playerCount = 2 << n;
    this->winningPlayer = winningPlayer;
}

Player *DataGenerator::getWinningPlayer() const
{
    return winPlayer;
}

std::vector<Player *> DataGenerator::generatePlayers()
{
    std::vector<Pair> matchUps;
    for(int i = 1; i < playerCount; i++)
    {
        for (int j = i + 1; j <= playerCount; j++)
        {
            matchUps.emplace_back(Pair(i, j));
        }
    }

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::bernoulli_distribution dis{0.5};

    for(auto i: matchUps)
    {
        i.result = dis(gen);
    }

    std::vector<Player*> result;
    for(int i = 0; i < playerCount; i++)
    {
        auto player = new Player(i);
        result.push_back(player);
    }

    for(auto i: result)
    {
        for(auto j: matchUps)
        {
            if(j.left == i->getId())
            {
                if (j.result)
                {
                    i->addLosingOpponent(result.at(j.right));
                }
                else
                {
                    i->addWinningOpponent(result.at(j.right));
                }
            }
            else if(j.right == i->getId())
            {
                if(j.result)
                {
                    i->addWinningOpponent(result.at(j.left));
                }
                else
                {
                    i->addLosingOpponent(result.at(j.left));
                }
            }
        }
    }

    if(winningPlayer != 0)
    {
        winPlayer = result.at(winningPlayer);
    }
    else
    {
        std::random_device rd2;
        std::mt19937 gen2{rd()};
        std::uniform_int_distribution<> dis2{1, playerCount};

        winPlayer = result.at(dis2(gen2));
    }

    return result;
}
