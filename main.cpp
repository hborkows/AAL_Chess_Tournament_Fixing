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
            std::cin >> playerCount;
            std::cin >> winningPlayer;
            std::cin >> alg;
            int left, right;
            bool leftWins;
            std::vector<Pair> matchUps;

            while(std::cin >> left >> right >> leftWins)
            {
                matchUps.emplace_back(Pair(left, right, leftWins));
            }

            DataGenerator dg(playerCount, winningPlayer);
            GameTree gameTree(dg.generatePlayersNotRand(matchUps));
            gameTree.setWinningPlayer(dg.getWinningPlayer());
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
                    return 1;
                }
                i++;
                winningPlayer = std::stoi(std::string(argv[i]));

                DataGenerator dg(playerCount,winningPlayer);
                GameTree gameTree(dg.generatePlayers());
                gameTree.setWinningPlayer(dg.getWinningPlayer());
                Interface interface(&gameTree, &dg);

                interface.solveRandomData(alg);
            }
            else
            {
                std::cout << "Too few arguments!" << std::endl;
            }
        }
        else if (strcmp(argv[i], "-mode3") == 0)
        {
            if (argc > 5)
            {
                i++;
                playerCount = static_cast<size_t>(std::stoi(std::string(argv[i])));
                i++;
                alg = static_cast<size_t>(std::stoi(std::string(argv[i])));
                i++;
                int repeatNum = std::stoi(std::string(argv[i]));
                i++;
                std::string fileName(argv[i]);
                bool stop;

                for(int j = 1; j <= playerCount; j++)
                {

                    for(int k = 0; k < repeatNum; k++)
                    {
                        stop = false;
                        while(!stop)
                        {
                            DataGenerator dg(j, -1);
                            GameTree gameTree(dg.generatePlayers());
                            gameTree.setWinningPlayer(dg.getWinningPlayer());
                            Interface interface(&gameTree, &dg);

                            stop = interface.solveMeasureTime(alg);
                            interface.writeToFile(fileName);
                        }
                    }
                }
            }
            else
            {
                std::cout << "Too few arguments!" << std::endl;
            }
        }
        else if (strcmp(argv[i], "-help") == 0)
        {
            std::cout << "-mode1 - manual data input" << std::endl;
            std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
            std::cout << "-mode2 - random data" << std::endl;
            std::cout << std::endl;
            std::cout << "-mode2 [n] [algorithm] [winning player]" << std::endl;
            std::cout << "[n] - number of players is 2^n" << std::endl;
            std::cout << "[algorithm] - 1 - brute force, 2 - brute force with players sorted by strength" << std::endl;
            std::cout << "[winning player] - number from range [0, 2^n)" << std::endl;
            std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
            std::cout << "-mode3 - random data with various problem instances and time measurement" << std::endl;
            std::cout << std::endl;
            std::cout << "-mode3 [n] [algorithm] [number of repeats] [output file]" << std::endl;
            std::cout << "[n] - number of players is 2^n" << std::endl;
            std::cout << "[algorithm] - 1 - brute force, 2 - brute force with players sorted by strength" << std::endl;
            std::cout << "[number of repeats] - number of times algorithm is measured for one number of players" << std::endl;
            std::cout << "[output file] - name of a csv file where results are to be stored" << std::endl;
            std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
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