#include <iostream>
#include <cstring>
#include <string>
#include "GameTree.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        //GameTree gameTree();
        int i = 1;
        size_t playerCount;
        size_t alg;
        size_t winningPlayer;

        if (strcmp(argv[i], "-mode1") == 0)
        {

        }
        else if (strcmp(argv[i], "-mode2") == 0)
        {
            if (argc > 4)
            {
                //DataGenerator dg();
                i++;
                playerCount = static_cast<size_t>(std::stoi(std::string(argv[i])));
                i++;
                alg = static_cast<size_t>(std::stoi(std::string(argv[i])));
                i++;
                winningPlayer = static_cast<size_t>(std::stoi(std::string(argv[i])));

                switch (alg)
                {
                    case 1:

                        break;
                    case 2:

                        break;
                    case 3:

                        break;
                    case 4:

                        break;
                    default:
                        break;
                }
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
                alg = static_cast<size_t>(std::stoi(std::string(argv[i])));
                i++;
                winningPlayer = static_cast<size_t>(std::stoi(std::string(argv[i])));

                switch (alg)
                {
                    case 1:

                        break;
                    case 2:

                        break;
                    case 3:

                        break;
                    case 4:

                        break;
                    default:
                        break;
                }
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
}