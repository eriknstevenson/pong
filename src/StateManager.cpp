//
// Created by Erik Stevenson on 9/14/17.
//

#include "State.h"
#include "StateManager.h"

void StateManager::set(std::unique_ptr<State> state) {
    if (!states.empty())
        pop();
    push(std::move(state));

}

void StateManager::push(std::unique_ptr<State> state) {
    states.push_back(std::move(state));
    states.back()->Enter();
}

void StateManager::pop() {
    if (!states.empty()) {
        states.back()->Leave();
        states.pop_back();
    }
    if (empty()) {
        window.close();
    }
}

void StateManager::Draw() {
    for (int i = 0; i < states.size(); ++i) {
        states[i]->Draw(window);
    }
}

void StateManager::Update(const sf::Time time) {
    states.back()->Update(time);
}

void StateManager::HandleEvent(sf::Event e) {
    states.back()->HandleEvent(e);
}

bool StateManager::empty() {
    return states.empty();
}
