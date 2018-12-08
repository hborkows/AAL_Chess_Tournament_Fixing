//
// Created by hborkows on 06.12.18.
//

#include "Player.h"

Player::Player(std::vector<Player> losingOpponents, std::vector<Player> winningOpponents, std::string id) : id(id)
{
    this->losingOpponents = losingOpponents;
    this->winningOpponents = winningOpponents;
}

void Player::sortOpponents()
{
    std::sort(losingOpponents.begin(), losingOpponents.end());
}

Player& Player::operator=(const Player &other)
{
    this->id = other.id;
    this->strength = other.strength;
    this->losingOpponents = other.losingOpponents;
    this->winningOpponents = other.winningOpponents;
}