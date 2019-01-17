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

Node::Node(const Node &other)
{
    this->player1 = other.player1;
    this->player2 = other.player2;
    this->parent = other.parent;
    this->left = other.left;
    this->right = other.right;
}

GameTree::GameTree(std::vector<Player*> players)
{
    this->root = nullptr;
    this->winningPlayer = nullptr;
    this->players = players;
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

std::vector<Node *> GameTree::domains()
{
    std::vector<Node*> result = availNodes();

    for(int i = 0; i < result.size(); i++)
    {
        if(result[i]->player2 == nullptr)
            result.erase(result.begin() + i);
    }

    return result;
}


bool GameTree::domainEmpty()
{
    std::vector<Node*> dom = domains();

    for(auto i: dom)
    {
        if(i->player1->noLosingOpponents())
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

void GameTree::availNodesRec(Node *current, std::vector<Node *>& nodes)
{
    if(current != nullptr)
    {
        if(current->left != nullptr)
            availNodesRec(current->left, nodes);
        if(current->right != nullptr)
            availNodesRec(current->right, nodes);
        if(current->left == nullptr && current->right == nullptr && current->player2 == nullptr)
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
    current->player2->setUsed(true);

    if(!atLeaf)
    {
        for (auto i: current->player1->getLosingOpponents())
        {
            if(!(i->isUsed()))
            {
                if (leftDone)
                    break;
                if(current->left != nullptr)
                    current->left->player2->setUsed(false);
                deleteTree(current->left);
                current->left = new Node(current->player1, current);
                leftDone = placePlayersBrutalRec(current->left, i, depth);
            }
        }

        if(leftDone)
        {
            for (auto i: current->player2->getLosingOpponents())
            {
                if(!(i->isUsed()))
                {
                    if (rightDone)
                        break;
                    if(current->right != nullptr)
                        current->right->player2->setUsed(false);
                    deleteTree(current->right);
                    current->right = new Node(current->player2, current);
                    rightDone = placePlayersBrutalRec(current->right, i, depth);
                }
            }
        }
    }

    return atLeaf || (leftDone && rightDone);
}

Node* GameTree::placePlayersBrutal()
{
    bool flag = false;
    treeInit();

    for(auto i: winningPlayer->getLosingOpponents())
    {
        i->setUsed(true);
        flag = placePlayersBrutalRec(root, i, 0);
        if(flag)
            break;
        else
            i->setUsed(false);
    }

    if(!flag)
        root = nullptr;

    Node* result = root;
    root = nullptr;
    return result;
}

Node* GameTree::placePlayersStrength()
{
    playersStrengthInit();
    return placePlayersBrutal();
}

bool GameTree::placePlayersCSPRec(std::vector<Node*> nodes, int depth)
{
    depth++;

    if(nodes.empty())
        return true;

    Node* current = *nodes.begin();

    for(auto i: current->player1->getLosingOpponents())
    {
        if(!i->isUsed())
        {
            current->player2 = i;
            current->player2->setUsed(true);
            if(depth < treeDepth)
            {
                current->left = new Node(current->player1, current);
                current->right = new Node(current->player2, current);
            }

            if (domainEmpty())
                continue;

            std::vector<Node *> avail = availNodes();
            std::sort(avail.begin(), avail.end(), customLosingLess);

            if (placePlayersCSPRec(avail, depth))
                return true;
            else
            {
                current->player2->setUsed(false);
                current->player2 = nullptr;
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
    root->player1->setUsed(true);
    if(!placePlayersCSPRec(nodes, 0))
        root = nullptr;

    Node* result = root;
    root = nullptr;
    return result;
}

Node* GameTree::placePlayersCSPStrength()
{
    playersStrengthInit();
    return placePlayersCSP();
}
