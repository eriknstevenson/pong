//
// Created by Erik Stevenson on 9/16/17.
//

#include "Players/Computer.h"

Computer::Computer(Player::Side s) : Player(s) {}

Player::Command Computer::logic(const sf::FloatRect ballPosition, const float ballAngle) {

    if (updateTimer.getElapsedTime().asMilliseconds() < updateInterval) {
        if (holdTimer.getElapsedTime().asMilliseconds() > holdTime) {
            currentCommand = None;
        }
        return currentCommand;
    }

    updateTimer.restart();
    holdTimer.restart();

    bool comingTowardsUs =
            (side == Left && ballAngle > 90 && ballAngle < 270) ||
            (side == Right && (ballAngle < 90 || ballAngle > 270));

    sf::FloatRect bounds = getBounds();

    if (comingTowardsUs) {
        // If the ball is above the paddle
        if (ballPosition.top + ballPosition.height < bounds.top) {
            currentCommand = Up;
        // If the ball is below the paddle
        } else if (ballPosition.top > bounds.top + bounds.height) {
            currentCommand = Down;
        } else {
            currentCommand = None;
        }

    }else{
        currentCommand = None;
    }

    return currentCommand;
}