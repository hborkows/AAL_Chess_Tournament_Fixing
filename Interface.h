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

    void solveBasic(size_t algorithm);
    void solveRandomData(size_t algorithm);
    void solveMeasureTime(size_t algorithm);
};


#endif //AAL_INTERFACE_H
