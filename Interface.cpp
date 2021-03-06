//
// Created by hborkows on 07.12.18.
//

#include "Interface.h"

Interface::Interface(GameTree *gameTree, DataGenerator *dataGenerator, std::vector<Line>* lines)
{
    this->gameTree = gameTree;
    this->dataGenerator = dataGenerator;
    this->lines = lines;
}

void Interface::solveBasic(size_t algorithm)
{
    Node* resultRoot = nullptr;

    switch (algorithm)
    {
        case 1:
            resultRoot = gameTree->placePlayersBrutal();
            break;
        case 2:
            resultRoot = gameTree->placePlayersStrength();
            break;
        case 3:
            resultRoot = gameTree->placePlayersCSP();
            break;
        case 4:
            resultRoot = gameTree->placePlayersCSPStrength();
            break;
        default:
            break;
    }

    if(resultRoot != nullptr)
    {
        std::cout << "Winning Player: " << dataGenerator->getWinningPlayer()->getId() << std::endl;
        std::cout << "Calculated pairings in first round:" << std::endl;
        writeTree(resultRoot);
    }
    else
        std::cout << "Result not found." << std::endl;
}

void Interface::solveRandomData(size_t algorithm)

{
    Node* resultRoot = nullptr;

    switch (algorithm)
    {
        case 1:
            resultRoot = gameTree->placePlayersBrutal();
            break;
        case 2:
            resultRoot = gameTree->placePlayersStrength();
            break;
        case 3:
            resultRoot = gameTree->placePlayersCSP();
            break;
        case 4:
            resultRoot = gameTree->placePlayersCSPStrength();
            break;
        default:
            break;
    }

    if(resultRoot != nullptr)
    {
        std::cout << "Winning Player: " << dataGenerator->getWinningPlayer()->getId() << std::endl;
        std::cout << "Calculated pairings in first round:" << std::endl;
        writeTree(resultRoot);
        std::cout << "Match-ups:" << std::endl;
        writeMatchUps();
    }
    else
        std::cout << "Result not found." << std::endl;
}

bool Interface::solveMeasureTime(size_t algorithm)
{
    time_type start, end;
    duration_type timeElapsed;
    bool writeTime = false;
    int i = 0;

    //while(!writeTime)
    {
        //i++;
        start = std::chrono::system_clock::now();
        switch (algorithm)
        {
            case 1:
                writeTime = gameTree->placePlayersBrutal() != nullptr;
                break;
            case 2:
                writeTime = gameTree->placePlayersStrength() != nullptr;
                break;
            case 3:
                writeTime = gameTree->placePlayersCSP() != nullptr;
                break;
            case 4:
                writeTime = gameTree->placePlayersCSPStrength() != nullptr;
                break;
            default:
                break;
        }
    }
    end = std::chrono::system_clock::now();
    timeElapsed = end - start;
    if(writeTime)
    {
        lines->emplace_back(Line(static_cast<int>(log2(dataGenerator->getPlayerCount())), timeElapsed));
        std::cout << static_cast<int>(log2(dataGenerator->getPlayerCount())) << " " << timeElapsed.count() << " s"
                  << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

void Interface::writeTree(Node *root)
{
    if(root != nullptr)
    {
        if (root->left == nullptr && root->right == nullptr)
            std::cout << "[ " << root->player1->getId() << " , " << root->player2->getId() << " ]" << std::endl;
        else
        {
            writeTree(root->left);
            writeTree(root->right);
        }
    }
}

void Interface::writeMatchUps()
{
    for(auto i: dataGenerator->getMatchUps())
    {
        if(i.result)
            std::cout << "( " << i.left << " , " << i.right << " ) left wins" << std::endl;
        else
            std::cout << "( " << i.left << " , " << i.right << " ) right wins" << std::endl;
    }
}

Interface::Interface(GameTree * gt, DataGenerator *dg)
{
    this->dataGenerator = dg;
    this->gameTree = gt;
    this->lines = nullptr;
}
