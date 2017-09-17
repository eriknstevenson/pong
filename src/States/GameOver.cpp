//
// Created by Erik Stevenson on 9/17/17.
//

#include "States/GameOver.h"

GameOver::GameOver(StateManager &sm, sf::Font &f, const Result r) : State(sm), font(f) {
    text.setFont(font);
    text.setCharacterSize(64);
    text.setString(r == Result::Win ? "You Win!" : "You Lose!");
    text.setPosition(400, 300);
    auto bounds = text.getGlobalBounds();
    text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    background.setFillColor(sf::Color(0,0,0,150));
    background.setSize(sf::Vector2f(800, 600));
}

void GameOver::Draw(sf::RenderTarget &window) {
    window.clear(sf::Color::Black);
    window.draw(text);
}

void GameOver::Update(const sf::Time) {}

void GameOver::HandleEvent(const sf::Event e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            stateManager.pop();
            break;
    }
}
