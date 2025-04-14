#include "playerInput.h"
#include "../game/game.h"   
#include "../global/globals.h"
#include "../game/chessLogic.h"
#include "../entities/entities.h"

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
    if(game->entitiesList[y][x] == nullptr || game->entitiesList[y][x]->getColor() != game->getColor())
    {
        std::cout << "Invalid selection" << std::endl;
        game->setPlayer(nullptr);
        return;
    }
    else if(game->entitiesList[y][x]->getColor() == game->getColor())
    {
        game->setPlayer(game->entitiesList[y][x].get());
        return;
    }
    return;
}
else 
{
    if(game->entitiesList[y][x] == nullptr || game->entitiesList[y][x]->getColor() != player->getColor())
    {
        Move move = {player->getY(), player->getX(), y, x};
        std::cout << "Attempting move from: " << move.fromRow << " " << move.fromCol << " to: " << move.toRow << " " << move.toCol << std::endl;
        std::cout << "Player color: " << player->getColor() << std::endl;

        if(game->entitiesList[player->getY()][player->getX()] == nullptr)
        {
            std::cout << "Invalid move at player.cpp" << std::endl;
            game->setPlayer(nullptr);
            return;
        }

        if(checkMove(game->entitiesList, move, player->getColor()))
        {
            //deselects player
            game->setPlayer(nullptr);
            return;
        }
        else
        {
            std::cout << "Invalid move" << std::endl;
            
            game->setPlayer(nullptr);
            return;
        }
    }
    else 
    {
        if(game->entitiesList[y][x].get() == player)
        {
            game->setPlayer(nullptr);
            return;
        }
        game->setPlayer(game->entitiesList[y][x].get());
        return;
    }
}
return;
}

