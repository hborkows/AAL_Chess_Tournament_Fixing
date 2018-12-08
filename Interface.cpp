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
    //TODO
}

void Interface::solveRandomData(size_t algorithm)
{
    //TODO
}

void Interface::solveMeasureTime(size_t algorithm)
{
    //TODO
}