//
// Created by Erik Stevenson on 9/16/17.
//

#include "Players/Human.h"

Human::Human(Player::Side s) : Player(s) {}

Player::Command Human::logic(const sf::FloatRect ballPosition, const float ballAngle) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        return Player::Command::Up;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        return Player::Command::Down;
    }

    return Player::Command::None;
}