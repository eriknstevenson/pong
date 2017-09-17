//
// Created by Erik Stevenson on 9/14/17.
//
// Title is a menu that allows the user to select from several options, check the instructions, or begin the game.
//

#ifndef CSCI437_TITLE_H
#define CSCI437_TITLE_H


#include <iostream>
#include <memory>

#include "State.h"
#include "States/Instructions.h"
#include "States/Game.h"

class Title : public State {
public:
    // Title State Constructor
    // StateManager& - Parent StateManager object
    // sf::Texture& - Texture to use for sprites
    // sf::Font& - Font to use for text
    // sf::SoundBuffer& - Bounce off wall sound buffer
    // sf::SoundBuffer& - Bounce off paddle sound buffer
    // sf::SoundBuffer& - Scoring sound buffer
    Title(StateManager &, sf::Texture &, sf::Font &, sf::SoundBuffer &, sf::SoundBuffer &, sf::SoundBuffer &);

    void Update(const sf::Time);

    void Draw(sf::RenderTarget &);

    void HandleEvent(const sf::Event);

private:
    // Used to create/manage menu items
    struct Selection {
        sf::Text text;
        std::function<void()> selected;
        std::function<void()> left;
        std::function<void()> right;
    };

    sf::Texture &spriteSheet;
    sf::Sprite flame;

    sf::SoundBuffer bounceWallBuffer;
    sf::SoundBuffer bouncePaddleBuffer;
    sf::SoundBuffer scoreBuffer;
    sf::Sound keyPress;

    sf::Font &font;
    sf::Text title;
    sf::Text cursor;
    std::vector<Selection> selections;

    // Add a new menu item
    // std::string - caption of the menu item
    // std::function<void()> - lambda to call when item is selected
    // std::function<void()> - lambda to call when left arrow is pressed on item
    // std::function<void()> - lambda to call when right arrow is pressed on item
    // returns: index in selections vector corresponding to newly-created item
    int addSelection(const std::string caption, const std::function<void()>, const std::function<void()>,
                      const std::function<void()>);

    // Add a new menu item
    // This menu item does nothing when left/right arrow keys are pressed on it.
    // std::string - caption of the menu item
    // std::function<void()> - lambda to call when item is selected
    // returns: index in selections vector corresponding to newly-created item
    int addSelection(const std::string, const std::function<void()>);

    // Used to position where the selections begin to be located.
    const sf::Vector2f selectionsLocation{400.0f, 400.0f};
    static const int selectionsCharacterSize = 32;

    int currentSelection = 0;

    int difficulty = 0;
    const int maxDifficulty = 5;

    // Mute sound
    bool mute = false;
    int muteSelection = 0;
    // Toggles mute on/off and updates the cursor afterwards.
    void toggleMute();

    // When the cursor moves position (or when an item's text changes), this should be called to ensure that the cursor
    // gets repositioned, and it's string gets updated so that it is centered over the correct item.
    void updateCursorPosition();

};

#endif //CSCI437_TITLE_H
