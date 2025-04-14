#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
 
#include "../global/observer.h"
#include "../global/pch.h"
#include "../entities/entities.h"



class Game;
class PlayerInput {
public:
    PlayerInput(Game* game) : game(game), player(nullptr) {}
    // Handles key press events
    InputReader inputReader;
    void handleKeyPress(const sf::Event::KeyPressed& keyPressed);
    void handleMouseClick(sf::Vector2f mousePosition);
    bool mousePressed = false;

    Entity* player;
    Game* game;


    void setPlayer(Entity* newPlayer) {
        player = newPlayer;
    }
};

#endif // PLAYERINPUT_H
