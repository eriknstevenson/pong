//
// Created by Erik Stevenson on 9/16/17.
//
// Displays informational information to the user.
//

#ifndef CSCI437_INSTRUCTIONS_H
#define CSCI437_INSTRUCTIONS_H


#include "State.h"

class Instructions : public State {
public:
    Instructions(StateManager &, sf::Font &);

    void Update(const sf::Time);

    void Draw(sf::RenderTarget &);

    void HandleEvent(const sf::Event);

    void Enter();

    void Leave();

private:

    sf::Font &font;
    sf::Text title;
    sf::Text instructions;

};



#endif //CSCI437_INSTRUCTIONS_H
