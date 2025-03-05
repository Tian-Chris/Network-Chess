#include "cell.h"

    
Cell::Cell(sf::Texture& texture, sf::Vector2f pos) 
    : 
    sprite(texture), 
    brightness(1), 
    position(pos) {
}

