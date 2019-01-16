#include <iostream>
#include <cstring>
#include <string>
#include "GameTree.h"
#include "DataGenerator.h"
#include "Interface.h"

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        int i = 1;
        size_t playerCount;
        size_t alg;
        int winningPlayer;

        if (strcmp(argv[i], "-mode1") == 0)
        {
            //std::cin >> playerCount;
            //std::cin >> winningPlayer;
            //std::cin >> alg;
            int left, right;
            bool leftWins;
            std::vector<Pair> matchUps;

//            while(std::cin >> left >> right >> leftWins)
//            {
//                matchUps.emplace_back(Pair(left, right, leftWins));
//            }

            playerCount = 2;
            winningPlayer = 0;
            alg = 3;

            matchUps.emplace_back(Pair(0, 1, true));
            matchUps.emplace_back(Pair(0, 2, false));
            matchUps.emplace_back(Pair(0, 3, true));
            matchUps.emplace_back(Pair(1, 2, false));
            matchUps.emplace_back(Pair(1, 3, true));
            matchUps.emplace_back(Pair(2, 3, false));

            DataGenerator dg(playerCount, winningPlayer);
            GameTree gameTree(dg.getWinningPlayer(), dg.generatePlayersNotRand(matchUps));
            Interface interface(&gameTree, &dg);

            interface.solveBasic(alg);
        }
        else if (strcmp(argv[i], "-mode2") == 0)
        {
            if (argc > 4)
            {
                i++;
                playerCount = static_cast<size_t>(std::stoi(std::string(argv[i])));
                i++;
                alg = static_cast<size_t>(std::stoi(std::string(argv[i])));
                if(alg > 4 || alg < 1)
                {
                    std::cout << "Wrong algorithm argument!" << std::endl;
                    return -1;
                }
                i++;
                winningPlayer = std::stoi(std::string(argv[i]));

                auto dg = new DataGenerator(playerCount,winningPlayer);
                auto gameTree = new GameTree(dg->getWinningPlayer(), dg->generatePlayers());
                Interface interface(gameTree, dg);

                interface.solveRandomData(alg);
            }
            else
            {
                std::cout << "Too few arguments!" << std::endl;
            }
        }
        else if (strcmp(argv[i], "-mode3") == 0)
        {
            if (argc > 4)
            {
                //DataGenerator dg();
                i++;
                playerCount = static_cast<size_t>(std::stoi(std::string(argv[i])));
                i++;
                winningPlayer = std::stoi(std::string(argv[i]));

                //DataGenerator dg(playerCount,winningPlayer);
                //GameTree gameTree(dg.getWinningPlayer(), dg.generatePlayers());


            }
            else
            {
                std::cout << "Too few arguments!" << std::endl;
            }
        }
        else if (strcmp(argv[i], "-help") == 0)
        {

        }
        else
        {
            std::cout << "Wrong argument!" << std::endl;
        }
    }
    else
    {
        std::cout << "Too few arguments! Try with -help" << std::endl;
    }

    return 0;
}