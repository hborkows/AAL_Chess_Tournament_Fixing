//
// Created by hborkows on 07.12.18.
//

#ifndef AAL_GAMETREE_H
#define AAL_GAMETREE_H

#include <cmath>
#include "Player.h"

struct Node
{
    Node* parent;
    Node* left;
    Node* right;
    Player* player1;
    Player* player2;

    Node(Player*, Node* parent);
};

class GameTree
{
    Node* root;
    size_t treeDepth;

    std::vector<Player*> players;
    Player* winningPlayer;

    void treeInit();
    void deleteTree(Node* node);
    bool placePlayersBrutalRec(Node* current, Player* losingPlayer, size_t depth);
    bool placePlayersCSPRec(Node* current, Player* losingPlayer, size_t depth);
    bool placePlayersCSPStrengthRec(Node* current, Player* losingPlayer, size_t depth);

public:
    GameTree() = default;
    GameTree(Player* winningPlayer, std::vector<Player*> players);
    ~GameTree();

    Node* placePlayersBrutal();
    Node* placePlayersStrength();
    Node* placePlayersCSP();
    Node* placePlayersCSPStrength();
};


#endif //AAL_GAMETREE_H
