//
// Created by Erik Stevenson on 9/16/17.
//

#include "States/Pause.h"

Pause::Pause(StateManager &sm, sf::Font &f) : State(sm), font(f) {
    text.setFont(font);
    text.setCharacterSize(64);
    text.setString("~ Paused ~");
    text.setPosition(400, 300);
    auto bounds = text.getGlobalBounds();
    text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    background.setFillColor(sf::Color(0,0,0,150));
    background.setSize(sf::Vector2f(800, 600));
}

void Pause::HandleEvent(const sf::Event e) {
    switch (e.type){
        case sf::Event::KeyPressed:
            stateManager.pop();
            break;
    }
}

void Pause::Update(const sf::Time) {}

void Pause::Draw(sf::RenderTarget &window) {
    window.draw(background);
    window.draw(text);
}