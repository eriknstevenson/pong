//
// Created by Erik Stevenson on 9/16/17.
//

#include <iostream>

#include "States/Game.h"
#include "States/GameOver.h"

Game::Game(StateManager &sm, sf::Font &f, sf::SoundBuffer &bounceWallBuf, sf::SoundBuffer &bouncePaddleBuf,
           sf::SoundBuffer &scoreBuf, bool mute, int difficulty) :
        State(sm),
        font(f),
        bounceWallBuffer(bounceWallBuf),
        bouncePaddleBuffer(bouncePaddleBuf),
        scoreBuffer(scoreBuf),
        human(Player::Side::Left),
        computer(Player::Side::Right),
        ball(difficulty, bounceWallSound, mute) {

    if (!bufferTexture.create(800, 600)) {
        auto error = "Unable to create render texture";
        throw std::runtime_error(error);
    }

    bufferTexture.clear(sf::Color::Black);
    bufferSprite.setTexture(bufferTexture.getTexture());

    background.setFillColor(sf::Color(0, 0, 0, 32));
    background.setSize(sf::Vector2f(800, 600));

    net.setFillColor(sf::Color::White);
    net.setSize(sf::Vector2f(8, 600));
    net.setOrigin(net.getSize() / 2.0f);
    net.setPosition(400, 300);

    score.setFont(font);
    score.setCharacterSize(64);
    score.setPosition(400, 5);
    score.setOrigin(score.getGlobalBounds().width / 2.0f, 0);
    updateScore();

    bouncePaddleSound.setBuffer(bouncePaddleBuffer);
    scoreSound.setBuffer(scoreBuffer);
    bounceWallSound.setBuffer(bounceWallBuffer);


    this->difficulty = difficulty;
    this->mute = mute;
}

void Game::HandleEvent(const sf::Event e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            switch (e.key.code) {
                case sf::Keyboard::P:
                    stateManager.push(std::unique_ptr<State>(new Pause(stateManager, font)));
                    break;
                case sf::Keyboard::A:
                    std::cout << ball.getAngle() << std::endl;
                    break;
                default:
                    return;

            }
            break;
        case sf::Event::LostFocus:
            stateManager.push(std::unique_ptr<State>(new Pause(stateManager, font)));
            break;
        default:
            return;
    }
}

void Game::Update(const sf::Time elapsed) {
    ball.update(elapsed);

    auto ballBounds = ball.getBounds();

    if (ballBounds.left < 0) {
        computer.addPoint();
        updateScore();
        ball.reset(difficulty);
        if (!mute) scoreSound.play();
    } else if (ballBounds.left + ballBounds.width > 800) {
        human.addPoint();
        updateScore();
        ball.reset(difficulty);
        if (!mute) scoreSound.play();
    }

    human.update(elapsed, ballBounds, ball.getAngle());
    computer.update(elapsed, ballBounds, ball.getAngle());

    // check for collision with paddles

    if (ball.getAngle() > 90 && ball.getAngle() < 270) {
        // If the ball is heading left.
        auto humanBounds = human.getBounds();
        if (ballBounds.left < 100 &&
            ballBounds.left <= humanBounds.left + humanBounds.width &&
            ballBounds.top <= humanBounds.top + humanBounds.height &&
            ballBounds.top + ballBounds.height >= humanBounds.top &&
            ballBounds.left + ballBounds.width >= humanBounds.left) {
            ball.bounceVerticalSurface(human.getSpeed());
            if (!mute) bouncePaddleSound.play();
        }
    } else {
        auto computerBounds = computer.getBounds();
        if (ballBounds.left > 700 &&
            ballBounds.left <= computerBounds.left + computerBounds.width &&
            ballBounds.top <= computerBounds.top + computerBounds.height &&
            ballBounds.top + ballBounds.height >= computerBounds.top &&
            ballBounds.left + ballBounds.width >= computerBounds.left) {
            ball.bounceVerticalSurface(computer.getSpeed());
            if (!mute) bouncePaddleSound.play();
        }
    }
}

void Game::Draw(sf::RenderTarget &window) {
    window.clear(sf::Color::Black);

    bufferTexture.draw(background);

    bufferTexture.draw(net);
    human.draw(bufferTexture);
    computer.draw(bufferTexture);
    ball.draw(bufferTexture);
    bufferTexture.draw(score);


    bufferTexture.display();
    window.draw(bufferSprite);
}

void Game::updateScore() {
    const int humanScore = human.getScore();
    const int computerScore = computer.getScore();
    if (humanScore >= 11) {
        stateManager.set(std::unique_ptr<State>(new GameOver(stateManager, font, GameOver::Win)));
    } else if (computerScore >= 11) {
        stateManager.set(std::unique_ptr<State>(new GameOver(stateManager, font, GameOver::Lose)));
    } else {
        score.setString(std::to_string(human.getScore()) + "   " + std::to_string(computer.getScore()));
        score.setOrigin(score.getGlobalBounds().width / 2.0f, 0);
    }
}