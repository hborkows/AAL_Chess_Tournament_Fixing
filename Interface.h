//
// Created by hborkows on 07.12.18.
//

#ifndef AAL_INTERFACE_H
#define AAL_INTERFACE_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <vector>
#include "GameTree.h"
#include "DataGenerator.h"

using time_type = std::chrono::time_point<std::chrono::system_clock>;
using duration_type = std::chrono::duration<double>;

struct Line
{
    int playerCount;
    duration_type duration;

    Line(int playerCount, duration_type duration): playerCount(playerCount), duration(duration) {};
};

class Interface
{
    GameTree* gameTree;
    DataGenerator* dataGenerator;
    std::vector<Line>* lines;

    void writeTree(Node* root);
    void writeMatchUps();

public:
    Interface(GameTree*, DataGenerator*);
    Interface(GameTree*, DataGenerator*, std::vector<Line>* lines);

    void solveBasic(size_t algorithm);
    void solveRandomData(size_t algorithm);
    bool solveMeasureTime(size_t algorithm);
};


#endif //AAL_INTERFACE_H
