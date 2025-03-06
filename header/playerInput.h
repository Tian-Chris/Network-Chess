#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H
#include "game.h"

class PlayerInput {
public:
    static void handleKeyPress(Game& game, const sf::Event::KeyPressed& keyPressed);
};

#endif 