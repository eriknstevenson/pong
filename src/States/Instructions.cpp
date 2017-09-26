//
// Created by Erik Stevenson on 9/16/17.
//

#include "States/Instructions.h"

Instructions::Instructions(StateManager &sm, sf::Font &f) :
        State(sm),
        font(f) {

    title.setFont(font);
    title.setString("You need instructions.\nFor a pong game?\n\nOkay...");
    title.setCharacterSize(24);
    title.setPosition(400, 100);
    title.setStyle(sf::Text::Bold);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);

    std::vector<std::string> steps{
            "Use the arrow keys.",
            "Beat the AI with your paddle.",
            "Be the first to get to 11.",
            "",
            "Press P to pause the game.",
            "Press F1 to view some info.",
            "",
            "<press any key>"
    };

    instructions.setFont(font);
    // "Fold" the vector of strings, inserting newlines between each line
    instructions.setString(std::accumulate(std::begin(steps), std::end(steps), std::string(),
                                           [](std::string &acc, std::string &s) { return acc + "\n" + s; }));

    instructions.setCharacterSize(16);
    instructions.setPosition(400, 300);
    instructions.setOrigin(instructions.getGlobalBounds().width / 2, instructions.getGlobalBounds().height / 2);
    instructions.setFillColor(sf::Color::White);


}

void Instructions::Draw(sf::RenderTarget &window) {
    window.clear(sf::Color::Black);
    window.draw(title);
    window.draw(instructions);
}

void Instructions::Update(const sf::Time) {}

void Instructions::HandleEvent(const sf::Event e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            stateManager.pop();
            break;
        default:
            return;
    }
}

void Instructions::Enter() {}

void Instructions::Leave() {}