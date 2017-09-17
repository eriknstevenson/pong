//
// Created by Erik Stevenson on 9/11/17.
//
// Loads and stores all resources needed by game.
// Starts the game at the Title screen.
// Contains the main game loop which drives drawing and updating of the game.
// Handles events, and passes unhandled events to the StateManager for processing.
//

#ifndef CSCI437_PONG_H
#define CSCI437_PONG_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "StateManager.h"
#include "States/Title.h"

class Pong
{
  public:

    Pong();
    // Begin the game loop
    void Run();

  private:
    sf::RenderWindow window;
    sf::Clock clock;

    sf::Clock fpsClock;
    sf::Font font;
    sf::Texture spriteSheet;

    sf::SoundBuffer bouncePaddleBuffer;
    sf::SoundBuffer bounceWallBuffer;
    sf::SoundBuffer scoreBuffer;

    StateManager stateManager;
    int fps;
    int framesDrawn;
    bool showInfo = false;
    sf::Text info;


    void update();
    void draw();
    void handleEvents();
};

#endif //CSCI437_PONG_H
