//
// Created by Erik Stevenson on 9/16/17.
//

#ifndef CSCI437_BALL_H
#define CSCI437_BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

class Ball {
public:
    // Ball Constructor
    // int - difficulty (translates to speed of ball)
    // sf::Sound& - bounce off wall sound effect
    // bool - Mute sounds
    Ball(const int, sf::Sound &, const bool);

    // Get bounding box of ball shape
    sf::FloatRect getBounds();

    // Returns current angle of travel
    float getAngle();

    // Draw the ball on specified target
    void draw(sf::RenderTarget &);

    // Update the balls position
    void update(const sf::Time);

    // Move the ball back to the center of the game screen, resetting speed, and choosing a new random angle of travel
    void reset(const int);

    // Bounce + add random variation to ball's angle
    void bounceHorizontalSurface();

    // Bounce + add random variation to ball's angle
    // float - paddle speed when contact is made.
    void bounceVerticalSurface(const float);

    // Step up ball's speed of travel.
    void increaseSpeed();

private:
    sf::Vector2f position;
    float angle;
    float speed;
    sf::Sound &bounceWall;
    sf::CircleShape ball;
    std::default_random_engine rng;
    std::uniform_int_distribution<int> initialAngleDist;
    std::uniform_real_distribution<float> bounceDist;

    bool mute;
};


#endif //CSCI437_BALL_H
