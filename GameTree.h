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

    void treeInit();
    void deleteTree();
    std::vector<Player*> findLeaves();
    bool placePlayersBrutalRec(Node* current, Player* losingPlayer, size_t depth);

public:
    Player* winningPlayer;

    GameTree() = default;
    GameTree(Player* winningPlayer, std::vector<Player*> players);
    ~GameTree();

    std::vector<Player*> placePlayersBrutal();
    std::vector<Player*> placePlayersStrength();
    std::vector<Player*> placePlayersCSP();
    std::vector<Player*> placePlayersCSPStrength();
};


#endif //AAL_GAMETREE_H
