//
// Created by hborkows on 07.12.18.
//

#include "DataGenerator.h"

DataGenerator::DataGenerator(size_t n, int winningPlayer)
{
    playerCount = 1 << n;
    this->winningPlayer = winningPlayer;
}

Player *DataGenerator::getWinningPlayer() const
{
    return winPlayer;
}

std::vector<Player *> DataGenerator::generatePlayers()
{
    srand(time(NULL));
    std::vector<Pair> matchUps;
    for(int i = 0; i < playerCount; i++)
    {
        for (int j = i + 1; j < playerCount; j++)
        {
            matchUps.emplace_back(Pair(i, j));
        }
    }

    for(auto i: matchUps)
    {
        i.result = static_cast<bool>(std::rand() % 2);
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

    if(winningPlayer != -1)
    {
        winPlayer = result.at(winningPlayer);
    }
    else
    {
        winPlayer = result.at(std::rand() % playerCount);
    }

    return result;
}

std::vector<Player *> DataGenerator::generatePlayersNotRand(std::vector<Pair> matchUps)
{
    std::vector<Player*> result;
    for(int i = 0; i <= static_cast<int>(log2(playerCount)); i++)
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

    winPlayer = result.at(winningPlayer);
    return result;
}
