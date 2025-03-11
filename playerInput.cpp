#include "header/playerInput.h"
#include "header/pch.h"
#include "header/game.h"   


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
        if(checkValidMove(game->player.y - 1, game->player.x))
        {
            game->player.move('w');
            game->viewDefault.setCenter(game->player.sprite.getPosition() + sf::Vector2f(game->gridSize / 2.f, game->gridSize / 2.f)); 
            game->viewZoom.setCenter(game->player.sprite.getPosition() + sf::Vector2f(game->gridSize / 2.f, game->gridSize / 2.f));  
            game->window->setView(game->viewDefault);    
        }              
    }

    if (keyPressed.scancode == sf::Keyboard::Scan::A) {
        if(checkValidMove(game->player.y, game->player.x - 1))
        {
            game->player.move('a');                    
            game->viewDefault.setCenter(game->player.sprite.getPosition() + sf::Vector2f(game->gridSize / 2.f, game->gridSize / 2.f)); 
            game->viewZoom.setCenter(game->player.sprite.getPosition() + sf::Vector2f(game->gridSize / 2.f, game->gridSize / 2.f));  
            game->window->setView(game->viewDefault);  
        }      
    }

    if (keyPressed.scancode == sf::Keyboard::Scan::S) {
        if(checkValidMove(game->player.y + 1, game->player.x))
        { 
            game->player.move('s');
            game->viewDefault.setCenter(game->player.sprite.getPosition() + sf::Vector2f(game->gridSize / 2.f, game->gridSize / 2.f)); 
            game->viewZoom.setCenter(game->player.sprite.getPosition() + sf::Vector2f(game->gridSize / 2.f, game->gridSize / 2.f));  
            game->window->setView(game->viewDefault);         
        }                  
    }                 

    if (keyPressed.scancode == sf::Keyboard::Scan::D) {
        if(checkValidMove(game->player.y, game->player.x + 1))
        {
            game->player.move('d');
            game->viewDefault.setCenter(game->player.sprite.getPosition() + sf::Vector2f(game->gridSize / 2.f, game->gridSize / 2.f)); 
            game->viewZoom.setCenter(game->player.sprite.getPosition() + sf::Vector2f(game->gridSize / 2.f, game->gridSize / 2.f));  
            game->window->setView(game->viewDefault);          
        }                  
    }
}



int PlayerInput::checkValidMove(int y, int x)
{
    int spriteType = game->obstacleLayer->grid[y][x].spriteType;
    std::cout << "Checking cell (" << y << ", " << x << ") with spriteType: " << spriteType << std::endl;
    if (game->obstacleLayer->grid[y][x].spriteType == 0)
    {
        return 1;
    }
    return 0;
}