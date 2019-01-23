//
// Created by hborkows on 07.12.18.
//

#include "DataGenerator.h"

DataGenerator::DataGenerator(size_t n, int winningPlayer)
{
    playerCount = 1 << n;
    this->winningPlayer = winningPlayer;
    matchUps = std::vector<Pair>();
}

Player *DataGenerator::getWinningPlayer() const
{
    return winPlayer;
}

std::vector<Player *> DataGenerator::generatePlayers()
{
    for(int i = 0; i < playerCount; i++)
    {
        for (int j = i + 1; j < playerCount; j++)
        {
            matchUps.emplace_back(Pair(i, j));
        }
    }

    std::random_device rand;
    std::mt19937 gen(rand());
    std::bernoulli_distribution dist;

    for(int i = 0; i < matchUps.size(); i++)
    {
        bool b = dist(gen);
        matchUps[i].result = b;
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

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, playerCount - 1);

    if(winningPlayer != -1)
    {
        winPlayer = result.at(winningPlayer);
    }
    else
    {
        while(true)
        {
            winPlayer = result.at(distr(eng));
            if (winPlayer != nullptr && winPlayer->getLosingOpponents().size() >= log2(playerCount))
                break;
        }

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
