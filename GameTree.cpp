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

std::vector<Node*> GameTree::availNodes()
{
    std::vector<Node*> result;
    availNodesRec(root, result);
    return result;
}

std::vector<Node*> GameTree::availNodesRec(Node *current, std::vector<Node *> nodes)
{
    if(current != nullptr)
    {
        if(current->left != nullptr)
            availNodesRec(current->left, nodes);
        if(current->right != nullptr)
            availNodesRec(current->right, nodes);
        if(current->left == nullptr && current->right == nullptr)
            nodes.push_back(current);
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
    playersStrengthInit();
    return placePlayersBrutal();
}

bool GameTree::placePlayersCSPRec(std::vector<Node*> nodes)
{
    if(nodes.empty())
        return true;

    Node* current = *nodes.begin();
    std::sort(current->player1->getWinningOpponents().begin(), current->player2->getWinningOpponents().end(), customWinningLess);

    for(auto i: current->player1->getLosingOpponents())
    {
        if(!i->isUsed())
        {
            current->player2 = i;
            current->player2->setUsed(true);
            current->left = new Node(current->player1, current);
            current->right = new Node(current->player2, current);

            if (domainEmpty())
                continue;

            std::vector<Node *> avail = availNodes();
            std::sort(avail.begin(), avail.end(), customLosingLess);

            if (placePlayersCSPRec(avail))
                return true;
            else
            {
                current->player2->setUsed(false);
                delete current->left;
                current->left = nullptr;
                delete current->right;
                current->right = nullptr;
            }
        }
    }

    return false;
}

Node* GameTree::placePlayersCSP()
{
    treeInit();
    std::vector<Node*> nodes = availNodes();
    placePlayersCSPRec(nodes);

    Node* result = root;
    root = nullptr;
    return result;
}

Node* GameTree::placePlayersCSPStrength()
{
    playersStrengthInit();
    return placePlayersCSP();
}
