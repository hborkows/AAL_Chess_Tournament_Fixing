//
// Created by hborkows on 07.12.18.
//

#include "GameTree.h"

Node::Node(Player* player, Node* parent)
{
    player1 = player;
    this->parent = parent;
}

GameTree::GameTree(Player *winningPlayer, std::vector<Player> players)
{
    this->winningPlayer = winningPlayer;
    this->players = players;
}

std::vector<Player> GameTree::placePlayersBrutal()
{
    //TODO
}

std::vector<Player> GameTree::placePlayersStrength()
{
    //TODO
}

std::vector<Player> GameTree::placePlayersCSP()
{
    //TODO
}

std::vector<Player> GameTree::placePlayersCSPStrength()
{
    //TODO
}