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

Node::Node(Player *player, Node *parent, int depth)
{
    player1 = player;
    this->parent = parent;
    this->left = nullptr;
    this->right = nullptr;
    this->depth = depth;
}

GameTree::GameTree(Player *winningPlayer, std::vector<Player*> players)
{
    this->root = nullptr;
    this->winningPlayer = winningPlayer;
    this->nodesToCheck = std::vector<Node*>();
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

bool GameTree::domainEmpty()
{
    for(auto i: players)
    {
        if(!(i->isUsed()))
            if(i->noLosingOpponents())
                return true;
    }
    return false;
}

void GameTree::deleteTree(Node* node)
{
    if(node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void GameTree::createTreeRec(Node* current, int currentDepth)
{
    if(currentDepth >= treeDepth)
        return;
    current->left = new Node(nullptr, nullptr, currentDepth);
    current->right = new Node(nullptr, nullptr, currentDepth);
    currentDepth++;
    createTreeRec(current->left, currentDepth);
    createTreeRec(current->right, currentDepth);
}

void GameTree::createTree()
{
    treeInit();
    createTreeRec(root, 1);
}

void GameTree::treeLevelRec(Node* current, int level, std::vector<Node *> nodes)
{
    if(current->depth == level)
    {
        nodes.push_back(current);
        return;
    }
    treeLevelRec(current->left, level, nodes);
    treeLevelRec(current->right, level, nodes);
}

std::vector<Node*> GameTree::treeLevel(int level)
{
    std::vector<Node*> result;
    treeLevelRec(root, level, result);
    return result;
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
    playersStrengthInit();
    return placePlayersBrutal();
}

bool GameTree::placePlayersCSPRec(Node *current, Player *losingPlayer, size_t depth)
{
    depth++;
    bool leftDone = false;
    bool rightDone = false;
    bool atLeaf = depth >= treeDepth;
    current->player2 = losingPlayer;
    std::vector<Node*> level = treeLevel(depth);

    if(!atLeaf)
    {

    }

//    if(!atLeaf)
//    {
//        for (auto i: current->player1->getLosingOpponents())
//        {
//            if (leftDone)
//                break;
//            deleteTree(current->left);
//            current->left = new Node(current->player1, current);
//            leftDone = placePlayersBrutalRec(current->left, i, depth);
//        }
//
//        if(leftDone)
//        {
//            for (auto i: current->player2->getLosingOpponents())
//            {
//                if (rightDone)
//                    break;
//                deleteTree(current->right);
//                current->right = new Node(current->player2, current);
//                rightDone = placePlayersBrutalRec(current->right, i, depth);
//            }
//        }
//    }

    return (leftDone && rightDone) || atLeaf;
}

Node* GameTree::placePlayersCSP()
{
    createTree();

    for(auto i: winningPlayer->getLosingOpponents())
    {
        if(placePlayersCSPRec(root,i,1))
            break;
    }

    Node* result = root;
    root = nullptr;
    return result;
}

Node* GameTree::placePlayersCSPStrength()
{
    playersStrengthInit();
    return placePlayersCSP();
}