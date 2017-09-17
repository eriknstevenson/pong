//
// Created by Erik Stevenson on 9/16/17.
//

#include "Player.h"

Player::Player(Side s) : side(s) {

    paddle.setSize(sf::Vector2f(16, 64));
    paddle.setFillColor(sf::Color::White);
    paddle.setOrigin(paddle.getSize() / 2.0f);
    position = 300;
}

void Player::addPoint() {
    score++;
}

int Player::getScore() {
    return score;
}

sf::FloatRect Player::getBounds() {
    return paddle.getGlobalBounds();
}

void Player::draw(sf::RenderTarget &window) {
    switch (side) {
        case Left:
            paddle.setPosition(30, position);
            break;
        case Right:
            paddle.setPosition(window.getSize().x - 30, position);
            break;
    };
    window.draw(paddle);
}

void Player::update(const sf::Time elapsed, const sf::FloatRect ballPosition, const float ballAngle) {

    // Get and process command
    auto command = logic(ballPosition, ballAngle);

    switch (command) {
        case Up:
            speed = std::max(-1 * maxSpeed, speed - 0.05f);
            break;
        case Down:
            speed = std::min(maxSpeed, speed + 0.05f);
            break;
    }

    // Move paddle
    position += speed * elapsed.asMilliseconds();
    speed = speed * 0.95f;

    // Stop the paddle at the top and bottom of the screen
    auto bounds = paddle.getGlobalBounds();
    if (bounds.top < 0) {
        speed = 0;
        position = 0 + bounds.height / 2;
    } else if (bounds.top + bounds.height > 600) {
        speed = 0;
        position = 600 - bounds.height / 2;
    }

    paddle.setPosition(paddle.getPosition().x, position);
}

float Player::getSpeed() {
    return speed;
}
