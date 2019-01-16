//
// Created by hborkows on 06.12.18.
//

#include "Player.h"

bool Player::noLosingOpponents()
{
    for(auto i: losingOpponents)
    {
        if(!(i->isUsed()))
            return false;
    }
    return true;
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

Player::Player(int id): id(id), losingOpponents(), winningOpponents()
{

}

void Player::addLosingOpponent(Player *opponent)
{
    losingOpponents.push_back(opponent);
}

void Player::addWinningOpponent(Player *opponent)
{
    winningOpponents.push_back(opponent);
}
