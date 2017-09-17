//
// Created by Erik Stevenson on 9/16/17.
//

#ifndef CSCI437_COMPUTER_H
#define CSCI437_COMPUTER_H

#include "Player.h"

class Computer : public Player {
public:
    Computer(Player::Side);
    Player::Command logic(const sf::FloatRect, const float);
private:
    // Used to control how frequently the Computer makes a new decision.
    // At an interval, the computer player chooses a new command. This command is held for holdTime,
    // then released until the next update.
    sf::Clock updateTimer;
    sf::Clock holdTimer;
    Player::Command currentCommand = Player::Command::None;
    // How frequently to update, in milliseconds
    const int updateInterval = 200;
    const int holdTime = 100;
};


#endif //CSCI437_COMPUTER_H
