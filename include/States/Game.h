//
// Created by Erik Stevenson on 9/16/17.
//

#ifndef CSCI437_GAME_H
#define CSCI437_GAME_H

#include "State.h"
#include "Player.h"
#include "States/Pause.h"
#include "Players/Computer.h"
#include "Players/Human.h"
#include "Ball.h"


class Game : public State {
public:
    // Game constructor
    // StateManager& - Parent StateManager object
    // sf::Font& - Font to use for text
    // sf::SoundBuffer& - Bounce off wall sound buffer
    // sf::SoundBuffer& - Bounce off paddle sound buffer
    // sf::SoundBuffer& - Scoring sound buffer
    // bool - mute sounds?
    // int - difficulty level
    Game(StateManager &, sf::Font &, sf::SoundBuffer &, sf::SoundBuffer &, sf::SoundBuffer &, const bool, const int);

    void Update(const sf::Time);

    void Draw(sf::RenderTarget &);

    void HandleEvent(const sf::Event);

private:
    sf::Font &font;
    sf::Text score;

    sf::RenderTexture bufferTexture;
    sf::Sprite bufferSprite;
    sf::RectangleShape background;

    sf::RectangleShape net;

    // All of the sounds
    sf::SoundBuffer &bounceWallBuffer;
    sf::SoundBuffer &bouncePaddleBuffer;
    sf::SoundBuffer &scoreBuffer;
    sf::Sound bounceWallSound;
    sf::Sound bouncePaddleSound;
    sf::Sound scoreSound;

    int difficulty = 0;
    bool mute = false;

    Ball ball;
    Human human;
    Computer computer;

    void updateScore();

};


#endif //CSCI437_GAME_H
