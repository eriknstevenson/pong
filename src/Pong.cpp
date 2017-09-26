//
// Created by Erik Stevenson on 9/11/17.
//

#include <iostream>

#include "Pong.h"


Pong::Pong() :
        window(sf::VideoMode(800, 600, 32), "CSCI437 - PONG",
               sf::Style::Titlebar | sf::Style::Close),
        stateManager(window) {

    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    // ****************
    // *Load resources*
    // ****************

    auto fontPath = "media/press-start-2p/PressStart2P-Regular.ttf";
    if (!font.loadFromFile(fontPath)) {
        const std::string error = std::string("file not found: ") + fontPath;
        throw std::runtime_error(error);
    }

    auto spriteSheetPath = "media/sprites.png";
    if (!spriteSheet.loadFromFile(spriteSheetPath)) {
        const std::string error = std::string("file not found: ") + spriteSheetPath;
        throw std::runtime_error(error);
    }
    spriteSheet.setSmooth(false);

    auto hitWallSFXPath = "media/bounce-wall.wav";
    if (!bounceWallBuffer.loadFromFile(hitWallSFXPath)) {
        const std::string error = std::string("file not found: ") + hitWallSFXPath;
        throw std::runtime_error(error);
    };

    auto hitPaddleSFXPath = "media/bounce-paddle.wav";
    if (!bouncePaddleBuffer.loadFromFile(hitPaddleSFXPath)) {
        const std::string error = std::string("file not found: ") + hitPaddleSFXPath;
        throw std::runtime_error(error);
    };

    auto scoreSFXPath = "media/score.wav";
    if (!scoreBuffer.loadFromFile(scoreSFXPath)) {
        const std::string error = std::string("file not found: ") + scoreSFXPath;
        throw std::runtime_error(error);
    };

    info.setFont(font);
    info.setFillColor(sf::Color::Green);
    info.setCharacterSize(16);
    info.setPosition(0, 0);

}

void Pong::Run() {
    stateManager.push(std::unique_ptr<State>(new Title(stateManager, spriteSheet, font, bounceWallBuffer, bouncePaddleBuffer, scoreBuffer)));

    while (window.isOpen()) {
        draw();
        update();
        handleEvents();
    }
}

void Pong::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed: {

                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        stateManager.pop();
                        break;

                    case sf::Keyboard::F1:
                        showInfo = !showInfo;
                        break;

                    default:
                        // Pass unhandled event down to the state manager
                        stateManager.HandleEvent(event);
                        break;
                }
                break;
            }
            default:
                // Pass unhandled event down to the state manager
                stateManager.HandleEvent(event);
                break;
        }
    }
}

void Pong::update() {
    sf::Time elapsed = clock.restart();
    stateManager.Update(elapsed);
}

void Pong::draw() {
    window.clear(sf::Color::Black);

    stateManager.Draw();

    if (showInfo) {
        info.setString(std::to_string(fps) + " FPS");
        window.draw(info);
    }

    window.display();

    // Count FPS
    framesDrawn++;
    if (fpsClock.getElapsedTime().asSeconds() > 1.0f) {
        fpsClock.restart();
        fps = framesDrawn;
        framesDrawn = 0;
    }


}
