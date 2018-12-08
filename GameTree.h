//
// Created by hborkows on 07.12.18.
//

#ifndef AAL_GAMETREE_H
#define AAL_GAMETREE_H

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
    Node* current;

    std::vector<Player> players;

public:
    Player* winningPlayer;

    GameTree() = default;
    GameTree(Player* winningPlayer, std::vector<Player> players);

    std::vector<Player> placePlayersBrutal();
    std::vector<Player> placePlayersStrength();
    std::vector<Player> placePlayersCSP();
    std::vector<Player> placePlayersCSPStrength();
};


#endif //AAL_GAMETREE_H
