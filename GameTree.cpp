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
    this->baseData = players;
    this->treeDepth = static_cast<size_t>(log2(players.size())); //use of static_cast, because number of players is specified to be 2^n
                                                                // and log2(2^n) = n which is an integer
}

GameTree::~GameTree()
{
    deleteTree(root);
}

void GameTree::treeInit()
{
    root = new Node(winningPlayer, nullptr);
}

void GameTree::playersStrengthInit()
{
    for(auto i: players)
    {
        i->calculateStrength();
    }

    for(auto i: players)
    {
        i->sortOpponents();
    }
}

//void GameTree::randomisePlayersStrength()
//{
//    for(auto i: players)
//    {
//        i->randomiseOpponents();
//    }
//}

void GameTree::deleteTree(Node* node)
{
    if(node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
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
        for (auto i: current->player1->getLosingOpponents())
        {
            if (leftDone)
                break;
            deleteTree(current->left);
            current->left = new Node(current->player1, current);
            leftDone = placePlayersBrutalRec(current->left, i, depth);
        }

        if(leftDone)
        {
            for (auto i: current->player2->getLosingOpponents())
            {
                if (rightDone)
                    break;
                deleteTree(current->right);
                current->right = new Node(current->player2, current);
                rightDone = placePlayersBrutalRec(current->right, i, depth);
            }
        }
    }

    return (leftDone && rightDone) || atLeaf;
}

Node* GameTree::placePlayersBrutal()
{
    treeInit();

    for(auto i: winningPlayer->getLosingOpponents())
    {
        if(placePlayersBrutalRec(root, i, 1))
            break;
    }

    Node* result = root;
    root = nullptr;
    return result;
}

Node* GameTree::placePlayersStrength()
{
    treeInit();
    playersStrengthInit();

    for(auto i: winningPlayer->getLosingOpponents())
    {
        if(placePlayersBrutalRec(root,i,1))
            break;
    }

    Node* result = root;
    root = nullptr;
    return result;
}

bool GameTree::placePlayersCSPRec(Node *current, Player *losingPlayer, size_t depth)
{
    //TODO
}

Node* GameTree::placePlayersCSP()
{
    treeInit();

    for(auto i: winningPlayer->getLosingOpponents())
    {
        if(placePlayersCSPRec(root,i,1))
            break;
    }

    Node* result = root;
    root = nullptr;
    return result;
}

bool GameTree::placePlayersCSPStrengthRec(Node *current, Player *losingPlayer, size_t depth)
{
    //TODO
}

Node* GameTree::placePlayersCSPStrength()
{
    //TODO
}