//
// Created by Erik Stevenson on 9/14/17.
//

#include "States/Title.h"

Title::Title(StateManager &sm, sf::Texture &t, sf::Font &f, sf::SoundBuffer &bounceWall, sf::SoundBuffer &bouncePaddle, sf::SoundBuffer &score) :
        State(sm),
        spriteSheet(t),
        font(f),
        bounceWallBuffer(bounceWall),
        bouncePaddleBuffer(bouncePaddle),
        scoreBuffer(score) {

    // Setup title text
    title.setFont(font);
    title.setString("PONG");
    title.setCharacterSize(64);
    title.setPosition(400, 300);
    title.setStyle(sf::Text::Bold);
    title.setOrigin(title.getGlobalBounds().width / 2.0f, title.getGlobalBounds().height / 2.0f);
    title.setColor(sf::Color::White);

    addSelection("start", [&]() {
        stateManager.push(std::unique_ptr<State>(new Game(stateManager, font, bounceWallBuffer, bouncePaddleBuffer, scoreBuffer, mute, difficulty)));
    });
    addSelection("difficulty", [&]() {
        difficulty = (difficulty + 1) % (maxDifficulty + 1);
    }, [&]() {
        // Left arrow
        difficulty = std::max(0, difficulty - 1);
    }, [&]() {
        // Right arrow
        difficulty = std::min(maxDifficulty, difficulty + 1);
    });
    muteSelection = addSelection("disable sound", [&]() {
        toggleMute();
    }, [&]() {
        // Left arrow
        toggleMute();
    }, [&]() {
        // Right arrow
        toggleMute();
    });
    addSelection("instructions", [&]() {
        stateManager.push(std::unique_ptr<State>(new Instructions(stateManager, font)));
    });
    addSelection("quit", [&]() {
        stateManager.pop();
    });

    cursor.setFont(font);
    cursor.setCharacterSize(selectionsCharacterSize);
    cursor.setColor(sf::Color::White);
    updateCursorPosition();

    flame.setTexture(spriteSheet);
    flame.setTextureRect(sf::IntRect(0, 0, 400, 300));
    flame.setScale(2.0f, 2.0f);

    keyPress.setBuffer(bounceWallBuffer);

}

void Title::Update(const sf::Time elapsed) {

}

void Title::Draw(sf::RenderTarget &window) {

    flame.setColor(sf::Color(255, 255, 255, sf::Uint8((float) difficulty * 255.0f / (float) maxDifficulty)));
    window.draw(flame);

    window.draw(title);
    window.draw(cursor);
    for (auto i = 0; i != selections.size(); ++i) {
        if (i == currentSelection) {
            selections[i].text.setStyle(sf::Text::Bold | sf::Text::Italic);
        } else {
            selections[i].text.setStyle(sf::Text::Regular);
        }

        window.draw(selections[i].text);
    }

}

void Title::HandleEvent(const sf::Event e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            if (!mute) keyPress.play();
            switch (e.key.code) {
                case sf::Keyboard::Down: {
                    currentSelection = std::min((int) selections.size() - 1, currentSelection + 1);
                    updateCursorPosition();
                    break;
                }
                case sf::Keyboard::Up: {
                    currentSelection = std::max(0, currentSelection - 1);
                    updateCursorPosition();
                    break;
                }
                case sf::Keyboard::Left: {
                    selections[currentSelection].left();
                    break;
                }
                case sf::Keyboard::Right: {
                    selections[currentSelection].right();
                    break;
                }
                case sf::Keyboard::Return:
                case sf::Keyboard::Space:
                    selections[currentSelection].selected();
                default:
                    return;
            }
            break;
        default:
            return;
    }
}

int Title::addSelection(const std::string caption, const std::function<void()> selected) {
    return addSelection(caption, selected, []() {}, []() {});
}

int Title::addSelection(const std::string caption, const std::function<void()> selected, const std::function<void()> left,
                    const std::function<void()> right) {

    sf::Text text;
    text.setFont(font);
    text.setString(caption);
    text.setColor(sf::Color::White);
    text.setCharacterSize(selectionsCharacterSize);

    auto bounds = text.getGlobalBounds();
    text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    text.setPosition(selectionsLocation.x, selectionsLocation.y + selections.size() * selectionsCharacterSize);

    selections.push_back(Selection{std::move(text), selected, left, right});
    return (int)selections.size() - 1;
}

void Title::updateCursorPosition() {
    cursor.setString(std::string(">") + std::string(selections[currentSelection].text.getString().getSize(), ' ') +
                     std::string("<"));
    cursor.setPosition(selectionsLocation.x, selectionsLocation.y + currentSelection * selectionsCharacterSize);
    auto bounds = cursor.getGlobalBounds();
    cursor.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Title::toggleMute() {
    mute = !mute;
    selections[muteSelection].text.setString(mute ? "enable sound" : "disable sound");
    auto bounds = selections[muteSelection].text.getGlobalBounds();
    selections[muteSelection].text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    updateCursorPosition();
}