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
    Node(const Node& other);
    Node(Node&& other) = default;
    Node& operator=(Node&& other) = default;
    
};

struct {
    bool operator()(Node* a, Node* b) const
    {
        return a->player1->getLosingOpponents().size() < b->player1->getLosingOpponents().size();
    }
} customLosingLess;

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
    std::vector<Node*> domains();
    void deleteTree(Node* node);
    void createTreeRec(Node* current, int currentDepth);
    std::vector<Node*> availNodes();
    void availNodesRec(Node* current, std::vector<Node *>& nodes);
    bool placePlayersBrutalRec(Node* current, Player* losingPlayer, size_t depth);
    bool placePlayersCSPRec(std::vector<Node*> nodes, int depth);

public:
    //GameTree() = default;
    GameTree(Player* winningPlayer, std::vector<Player*> players);
    ~GameTree();

    void resetplayerData() {players = baseData;};

    Node* placePlayersBrutal();
    Node* placePlayersStrength();
    Node* placePlayersCSP();
    Node* placePlayersCSPStrength();
};


#endif //AAL_GAMETREE_H
