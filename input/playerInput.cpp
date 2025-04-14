#include "playerInput.h"
#include "../game/game.h"   
#include "../global/globals.h"
//convert this into just a function instead of an object


// Handles key press events
void PlayerInput::handleKeyPress(const sf::Event::KeyPressed& keyPressed) {
    if (keyPressed.scancode == sf::Keyboard::Scan::Escape) {
        inputReader.notifyObservers("Esc");
        //game->window->close();
    }
    
    if (keyPressed.scancode == sf::Keyboard::Scan::Tab) 
    {
        inputReader.notifyObservers("Tab");
    } 
    
    if (keyPressed.scancode == sf::Keyboard::Scan::W) {
        //this subject will be observed by ui and networking
        inputReader.notifyObservers("w");
    }

    if (keyPressed.scancode == sf::Keyboard::Scan::A) {
        inputReader.notifyObservers("a");

    }

    if (keyPressed.scancode == sf::Keyboard::Scan::S) {
        inputReader.notifyObservers("s");
                  
    }                 

    if (keyPressed.scancode == sf::Keyboard::Scan::D) {
        inputReader.notifyObservers("d");
         
    }
}

void PlayerInput::handleMouseClick(sf::Vector2f mousePosition) {
player = game->getPlayer();
int x = static_cast<int>(mousePosition.x) / 32;
int y = static_cast<int>(mousePosition.y) / 32;

if(player == nullptr)
{
    if(game->entitiesList[x][y] == nullptr || game->entitiesList[x][y]->getColor() != game->getColor())
    {
        std::cout << "Invalid selection" << std::endl;
        game->setPlayer(nullptr);
        return;
    }
    else if(game->entitiesList[x][y]->getColor() == game->getColor())
    {
        game->setPlayer(game->entitiesList[x][y].get());
        return;
    }
    return;
}
else 
{
    if(game->entitiesList[x][y] == nullptr || game->entitiesList[x][y]->getColor() != player->getColor())
    {
        //checkMove will handle all logic
        // if(checkMove(game->entitiesList[x][y], x, y))
        // {
        //     player->setX(x); //moves the sprite of player
        //     player->setY(y);
        //     //replaces old pointer at destination with player unique ptr auto destructs
        //     game->entitiesList[x][y] = std::move(game->entitiesList[player->getX()][player->getY()]);
        //     //sets players prior position to nullptr
        //     game->entitiesList[player->getX()][player->getY()] = nullptr;
        //     //deselects player
        //     game->setPlayer(nullptr);
        //     return;
        // }
        // else
        // {
        //     std::cout << "Invalid move" << std::endl;
            
        //     game->setPlayer(nullptr);
        //     return;
        // }
    }
    else 
    {
        game->setPlayer(game->entitiesList[x][y].get());
        return;
    }
}
return;
}

