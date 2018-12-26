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
    int depth;
    Player* player1;
    Player* player2;

    Node(Player*, Node* parent);
    Node(Player*, Node* parent, int depth);
};

class GameTree
{
    Node* root;
    size_t treeDepth;

    std::vector<Player*> players;
    std::vector<Node*> nodesToCheck;
    std::vector<Player*> baseData;
    Player* winningPlayer;

    void treeInit();
    void playersStrengthInit();
    //void randomisePlayersStrength();
    bool domainEmpty();
    void deleteTree(Node* node);
    void createTree();
    void createTreeRec(Node* current, int currentDepth);
    std::vector<Node*> treeLevel(int level);
    void treeLevelRec(Node* current, int level, std::vector<Node*> nodes);
    bool placePlayersBrutalRec(Node* current, Player* losingPlayer, size_t depth);
    bool placePlayersCSPRec(Node* current, Player* losingPlayer, size_t depth);

public:
    GameTree() = default;
    GameTree(Player* winningPlayer, std::vector<Player*> players);
    ~GameTree();

    void resetplayerData() {players = baseData;};

    Node* placePlayersBrutal();
    Node* placePlayersStrength();
    Node* placePlayersCSP();
    Node* placePlayersCSPStrength();
};


#endif //AAL_GAMETREE_H
