//
// Created by Erik Stevenson on 9/16/17.
//
// This GameState draws a transparent pause indication over top of everything. Game will resume following a keypress.
//

#ifndef CSCI437_PAUSE_H
#define CSCI437_PAUSE_H

#include "State.h"

class Pause : public State {
public:
    Pause(StateManager &, sf::Font &);

    void Update(const sf::Time);
    void Draw(sf::RenderTarget &);
    void HandleEvent(const sf::Event);

private:
    sf::Font &font;
    sf::Text text;
    sf::RectangleShape background;
};


#endif //CSCI437_PAUSE_H
