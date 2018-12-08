//
// Created by hborkows on 07.12.18.
//

#ifndef AAL_INTERFACE_H
#define AAL_INTERFACE_H

#include "GameTree.h"
#include "DataGenerator.h"

class Interface
{
    GameTree* gameTree;
    DataGenerator* dataGenerator;

public:
    Interface(GameTree*, DataGenerator*);

    void solveBasic();
    void solveRandomData();
    void solveMeasureTime();
};


#endif //AAL_INTERFACE_H
