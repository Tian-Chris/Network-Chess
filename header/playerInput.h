#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
 
#include "observer.h"

class Game;

class PlayerInput {
public:
    // Constructor, takes a pointer to a Game object
    PlayerInput(Game* game);

    // Handles key press events
    void handleKeyPress(const sf::Event::KeyPressed& keyPressed);
    int checkValidMove(int x, int y);
    InputReader inputReader;
private:
    Game* game;  // Pointer to a Game object
};

#endif // PLAYERINPUT_H
