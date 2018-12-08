//
// Created by hborkows on 07.12.18.
//

#include "GameTree.h"

Node::Node(Player* player, Node* parent)
{
    player1 = player;
    this->parent = parent;
    this->left = nullptr;
    this->right = nullptr;
}

GameTree::GameTree(Player *winningPlayer, std::vector<Player*> players)
{
    this->root = nullptr;
    this->winningPlayer = winningPlayer;
    this->players = players;
    this->treeDepth = static_cast<size_t>(log2(players.size())); //use of static_cast, because number of players is specified to be 2^n
                                                                // and log2(2^n) = n which is an integer
}

GameTree::~GameTree()
{
    deleteTree();
}

void GameTree::treeInit()
{
    root = new Node(winningPlayer, nullptr);
}

void GameTree::deleteTree()
{
    //TODO
}

std::vector<Player*> GameTree::findLeaves()
{
    //TODO
}

bool GameTree::placePlayersBrutalRec(Node *current, Player *losingPlayer, size_t depth)
{
    depth++;
    bool leftDone = false;
    bool rightDone = false;
    bool atLeaf = depth >= treeDepth;
    current->player2 = losingPlayer;

    if(!atLeaf)
    {
        current->left = new Node(current->player1, current);
        current->right = new Node(current->player2, current);

        for (auto i: current->player1->getLosingOpponents())
        {
            if (leftDone)
                break;
            leftDone = placePlayersBrutalRec(current->left, i, depth);
        }

        for (auto i: current->player2->getLosingOpponents())
        {
            if (rightDone)
                break;
            rightDone = placePlayersBrutalRec(current->right, i, depth);
        }
    }

    return (leftDone && rightDone) || atLeaf;
}

std::vector<Player*> GameTree::placePlayersBrutal()
{
    treeInit();
    Node* current = root;

    for(auto i: winningPlayer->getLosingOpponents())
    {
        if(placePlayersBrutalRec(current, i, 1))
            break;
    }

    return findLeaves();
}

std::vector<Player*> GameTree::placePlayersStrength()
{
    //TODO
}

std::vector<Player*> GameTree::placePlayersCSP()
{
    //TODO
}

std::vector<Player*> GameTree::placePlayersCSPStrength()
{
    //TODO
}