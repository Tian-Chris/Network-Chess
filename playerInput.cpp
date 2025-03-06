#include "header/playerInput.h"
#include "header/pch.h"

//handles player input
void PlayerInput::handleKeyPress(Game& game, const sf::Event::KeyPressed& keyPressed)
{
    if (keyPressed.scancode == sf::Keyboard::Scan::Escape)
    {
        game.window -> close();
    }
    if ((keyPressed.scancode == sf::Keyboard::Scan::Tab) && (game.zoom == 1))
    {
        game.window -> setView(game.viewDefault);
        game.zoom = 0;
    }
    else if ((keyPressed.scancode == sf::Keyboard::Scan::Tab) && (game.zoom == 0))
    {
        game.window -> setView(game.viewZoom);
        game.zoom = 1;
    }
    if (keyPressed.scancode == sf::Keyboard::Scan::W)
    {
        game.player.move({0.f, -game.gridSize});
        game.viewDefault.setCenter(game.player.getPosition() + sf::Vector2f(game.gridSize / 2.f, game.gridSize / 2.f)); 
        game.viewZoom.setCenter(game.player.getPosition() + sf::Vector2f(game.gridSize / 2.f, game.gridSize / 2.f));  
        game.window -> setView(game.viewDefault);                  
    }
    if (keyPressed.scancode == sf::Keyboard::Scan::A)
    {
        game.player.move({-game.gridSize, 0.f});                    
        game.viewDefault.setCenter(game.player.getPosition() + sf::Vector2f(game.gridSize / 2.f, game.gridSize / 2.f)); 
        game.viewZoom.setCenter(game.player.getPosition() + sf::Vector2f(game.gridSize / 2.f, game.gridSize / 2.f));  
        game.window -> setView(game.viewDefault);        
    }
    if (keyPressed.scancode == sf::Keyboard::Scan::S)
    {
        game.player.move({0.f, game.gridSize});
        game.viewDefault.setCenter(game.player.getPosition() + sf::Vector2f(game.gridSize / 2.f, game.gridSize / 2.f)); 
        game.viewZoom.setCenter(game.player.getPosition() + sf::Vector2f(game.gridSize / 2.f, game.gridSize / 2.f));  
        game.window -> setView(game.viewDefault);                           
    }                
    if (keyPressed.scancode == sf::Keyboard::Scan::D)
    {
        game.player.move({game.gridSize, 0.f});
        game.viewDefault.setCenter(game.player.getPosition() + sf::Vector2f(game.gridSize / 2.f, game.gridSize / 2.f)); 
        game.viewZoom.setCenter(game.player.getPosition() + sf::Vector2f(game.gridSize / 2.f, game.gridSize / 2.f));  
        game.window -> setView(game.viewDefault);                            
    }                               
}
