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
