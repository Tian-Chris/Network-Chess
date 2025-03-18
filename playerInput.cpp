#include "header/playerInput.h"
#include "header/pch.h"
#include "header/game.h"   
#include "header/globals.h"

//convert this into just a function instead of an object

// Constructor that takes a pointer to a Game object
PlayerInput::PlayerInput(Game* game)
    : game(game) // Initialize the game pointer
{
}

// Handles key press events
void PlayerInput::handleKeyPress(const sf::Event::KeyPressed& keyPressed) {
    if (keyPressed.scancode == sf::Keyboard::Scan::Escape) {
        game->window->close();
    }
    
    if ((keyPressed.scancode == sf::Keyboard::Scan::Tab) && (game->zoom == 1)) {
        game->window->setView(game->viewDefault);
        game->zoom = 0;
    } else if ((keyPressed.scancode == sf::Keyboard::Scan::Tab) && (game->zoom == 0)) {
        game->window->setView(game->viewZoom);
        game->zoom = 1;
    }
    
    if (keyPressed.scancode == sf::Keyboard::Scan::W) {
        //this subject will be observed by ui and networking
        inputReader.notifyObservers("w");
        if(checkValidMove(game->player.y - 1, game->player.x))
        {
            game->player.move('w');
            game->viewDefault.setCenter(game->player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f)); 
            game->viewZoom.setCenter(game->player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));  
            game->window->setView(game->viewDefault);    
        }              
    }

    if (keyPressed.scancode == sf::Keyboard::Scan::A) {
        if(checkValidMove(game->player.y, game->player.x - 1))
        {
            game->player.move('a');                    
            game->viewDefault.setCenter(game->player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f)); 
            game->viewZoom.setCenter(game->player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));  
            game->window->setView(game->viewDefault);  
        }      
    }

    if (keyPressed.scancode == sf::Keyboard::Scan::S) {
        if(checkValidMove(game->player.y + 1, game->player.x))
        { 
            game->player.move('s');
            game->viewDefault.setCenter(game->player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f)); 
            game->viewZoom.setCenter(game->player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));  
            game->window->setView(game->viewDefault);         
        }                  
    }                 

    if (keyPressed.scancode == sf::Keyboard::Scan::D) {
        if(checkValidMove(game->player.y, game->player.x + 1))
        {
            game->player.move('d');
            game->viewDefault.setCenter(game->player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f)); 
            game->viewZoom.setCenter(game->player.sprite.getPosition() + sf::Vector2f(gridSize / 2.f, gridSize / 2.f));  
            game->window->setView(game->viewDefault);          
        }                  
    }
}


//place this elsewhere
int PlayerInput::checkValidMove(int y, int x)
{
    // Check if the pointer is not null
    if (game->obstacleLayer->grid[y][x] == nullptr) {
        return 1;
    }
    else
    {
        int spriteType = game->obstacleLayer->grid[y][x]->spriteType;
        
        // Check if the spriteType is not empty cell
        if (spriteType != 0) {
            return 0;  // invalid move (empty cell)
        }
    }

    return 1;  // valid move (either non-empty cell or nullptr)
}