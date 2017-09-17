//
// Created by Erik Stevenson on 9/16/17.
//

#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    // Used to specify which side of the screen the player will be on.
    enum Side {
        Left, Right
    };
    // Returned from the `logic` command, used to specify inputs from either Human/Computer
    enum Command{None, Up, Down};

    Player(Side);

    // Draw the paddle onto the specified target
    void draw(sf::RenderTarget &);

    // Update the player.
    // sf::Time - elapsed amount of time since last update.
    // sf::FloatRect - bounding area of ball (forwarded to logic, used for AI)
    // float - angle of ball (forwarded to logic, used for AI)
    void update(const sf::Time, const sf::FloatRect, const float);

    // Called to calculate how the paddle should move. Implemented differently by human/computer
    virtual Command logic(const sf::FloatRect, const float) = 0;

    // Add one point to the scoreboard
    void addPoint();

    // Returns the current score.
    int getScore();

    // Get the bounds of the rectangle shaped paddle. Used for collision detection
    sf::FloatRect getBounds();

    // Returns current speed.
    float getSpeed();

protected:
    Side side;

private:
    sf::RectangleShape paddle;

    float position = 0.0f; //y-position
    float speed = 0.0f;
    float maxSpeed = 1;
    int score = 0;
};


#endif //CSCI437_PLAYER_H
