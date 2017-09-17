//
// Created by Erik Stevenson on 9/16/17.
//

#include <iostream>
#include <chrono>
#include "Ball.h"

Ball::Ball(const int difficulty, sf::Sound &sound, const bool mute) :
        rng((unsigned long) std::chrono::system_clock::now().time_since_epoch().count()),
        initialAngleDist(0, 180),
        bounceDist(-5.0f, 5.0f),
        bounceWall(sound){
    ball.setFillColor(sf::Color::White);
    ball.setRadius(8);
    auto bounds = ball.getGlobalBounds();
    ball.setOrigin(bounds.width / 2, bounds.height / 2);
    reset(difficulty);

    this->mute = mute;
}

void Ball::reset(const int difficulty) {
    position = sf::Vector2f {400, 300};
    speed = 0.2f + 0.1f * difficulty;
    angle = initialAngleDist(rng);
    // Adjust the angle so that it points more towards the paddles than the walls.
    angle += (angle > 90 ? 1 : -1) * 45;
}

void Ball::draw(sf::RenderTarget &window) {
    ball.setPosition(position);
    window.draw(ball);
}

sf::FloatRect Ball::getBounds() {
    ball.setPosition(position);
    return ball.getGlobalBounds();
}

float Ball::getAngle() {
    return angle;
}

void Ball::update(const sf::Time elapsed) {
    position.x += speed * cos(angle / 180.f * 3.14159) * (float) elapsed.asMilliseconds();
    position.y -= speed * sin(angle / 180.f * 3.14159) * (float) elapsed.asMilliseconds();

    auto bounds = ball.getGlobalBounds();
    if (position.y - bounds.height / 2 < 0 || position.y + bounds.height / 2 > 600) {
        bounceHorizontalSurface();
        position.y = std::min(600.0f, std::max(position.y, 0.0f));

        // fix bug where ball gets stuck to wall
        if (position.y > 300) {
            if (angle > 180 && angle < 270) {
                angle = 179;
            } else if (angle > 270 && angle < 360) {
                angle = 1;
            }
        } else {
            if (angle < 180 && angle > 90) {
                angle = 181;
            } else if (angle < 90) {
                angle = 359;
            }
        }
    }
}

void Ball::increaseSpeed() {
    speed += 0.05f;
}

void Ball::bounceHorizontalSurface() {
    angle = 0 - angle;
    angle += bounceDist(rng);
    // Force angle to stay within 0-360
    angle = ((int) angle % 360 + 360) % 360;
    if (!mute) bounceWall.play();
}

void Ball::bounceVerticalSurface(const float paddleSpeed) {
    angle = 180 - angle;
    angle += bounceDist(rng);
    angle += paddleSpeed * -50;
    // Force angle to stay within 0-360
    angle = ((int) angle % 360 + 360) % 360;
    increaseSpeed();
}
