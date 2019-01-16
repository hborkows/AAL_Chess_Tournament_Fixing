//
// Created by hborkows on 07.12.18.
//

#include "Interface.h"

Interface::Interface(GameTree *gameTree, DataGenerator *dataGenerator)
{
    this->gameTree = gameTree;
    this->dataGenerator = dataGenerator;
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

    std::cout << "Winning Player: " << dataGenerator->getWinningPlayer()->getId() << std::endl;
    std::cout << "Calculated pairings in first round:" << std::endl;
    writeTree(resultRoot);
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

    std::cout << "Winning Player: " << dataGenerator->getWinningPlayer()->getId() << std::endl;
    std::cout << "Calculated pairings in first round:" << std::endl;
    writeTree(resultRoot);
}

void Interface::solveMeasureTime(size_t algorithm)
{

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
