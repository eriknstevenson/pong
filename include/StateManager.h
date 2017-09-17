//
// Created by Erik Stevenson on 9/14/17.
//
// This class manages a stack of game states.
//

#ifndef CSCI437_STATEMANAGER_H
#define CSCI437_STATEMANAGER_H


#include <memory>
#include <vector>

class State;

class StateManager {
private:
    sf::RenderWindow &window;
    std::vector<std::unique_ptr<State>> states;
public:
    StateManager(sf::RenderWindow &w) : window(w) {};

    // Replace the current game state, leaving the rest of the stack intact.
    void set(std::unique_ptr<State> state);

    // Push a new state onto the stack. This will become the state that gets updated.
    void push(std::unique_ptr<State> state);

    // Remove the top-most state. If there are no more states, the game is over.
    void pop();

    // Update only the active state
    void Update(const sf::Time);

    // Draw all states in the stack. This is used to have the pause screen overlayed on the top of the game screen.
    void Draw();

    // Forward unhandled events to the active state
    void HandleEvent(sf::Event);

    // Returns whether any states remain on the stack.s
    bool empty();
};


#endif //CSCI437_STATEMANAGER_H
