//
// Created by Erik Stevenson on 9/16/17.
//
// Human controller, polls keyboard for up/down arrows, returns the respective command.
//

#ifndef CSCI437_HUMAN_H
#define CSCI437_HUMAN_H

#include "Player.h"

class Human : public Player {
public:
    Human(Player::Side);
    Player::Command logic(const sf::FloatRect, const float);
};


#endif //CSCI437_HUMAN_H
