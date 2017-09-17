//
// Created by Erik Stevenson on 9/17/17.
//
// GameOver displays to the user the result of the game, and returns to the Title screen following a keypress.
//

#ifndef CSCI437_GAMEOVER_H
#define CSCI437_GAMEOVER_H


#include "State.h"

class GameOver : public State {
public:
    enum Result {Win, Lose};

    GameOver(StateManager &, sf::Font &, const Result);

    void Update(const sf::Time);
    void Draw(sf::RenderTarget &);
    void HandleEvent(const sf::Event);

private:
    sf::Font &font;
    sf::Text text;
    sf::RectangleShape background;
};


#endif //CSCI437_GAMEOVER_H
