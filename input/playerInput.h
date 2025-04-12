#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
 
#include "../global/observer.h"
#include "../global/pch.h"


class Game;

class PlayerInput {
public:
    // Handles key press events
    void handleKeyPress(const sf::Event::KeyPressed& keyPressed);
    InputReader inputReader;
    void handleMouseClick(const sf::Vector2i& mousePosition);
};

#endif // PLAYERINPUT_H
