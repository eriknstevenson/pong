//
// Created by Erik Stevenson on 9/11/17.
//

#ifndef CSCI437_STATE_H
#define CSCI437_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "StateManager.h"

class State {
public:
    State(StateManager &stateManager) : stateManager(stateManager) {};

    void LoadResources() {
        loaded = true;
    };

    virtual void Enter() {};

    virtual void Leave() {};

    virtual void Update(const sf::Time) = 0;

    virtual void Draw(sf::RenderTarget &) = 0;

    virtual void HandleEvent(const sf::Event) {};

    bool isLoaded() {
        return loaded;
    }

protected:
    bool loaded = false;
    StateManager &stateManager;
};

#endif //CSCI437_STATE_H
