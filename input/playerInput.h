#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
 
#include "../global/observer.h"

class Game;

class PlayerInput {
public:
    // Handles key press events
    void handleKeyPress(const sf::Event::KeyPressed& keyPressed);
    InputReader inputReader;
};

#endif // PLAYERINPUT_H
