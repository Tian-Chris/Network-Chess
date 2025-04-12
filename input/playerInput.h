#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
 
#include "../global/observer.h"
#include "../global/pch.h"


class Game;

class PlayerInput {
public:
    // Handles key press events
    InputReader inputReader;
    void handleKeyPress(const sf::Event::KeyPressed& keyPressed);
    void handleMouseClick(const sf::Vector2i& mousePosition);
    bool mousePressed = false;
    Entity* player;
    
};

#endif // PLAYERINPUT_H
