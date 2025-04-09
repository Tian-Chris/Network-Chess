#ifndef CELL_H
#define CELL_H
#include "../global/pch.h"
#include <memory> // Include for std::unique_ptr

using namespace std;

class Cell {
    public:
        sf::Vector2f position;  // Position of the cell
        int brightness;
        int spriteType;  // Represents the type of sprite (or texture)
        std::unique_ptr<sf::Sprite> sprite; // Use unique_ptr for sprite
        std::unordered_map<int, sf::Texture>* myTexture; // Reference to the texture map
    
        // Default constructor
        Cell();
    
        // Constructor with position and sprite type
        Cell(sf::Vector2f pos, int type, std::unordered_map<int, sf::Texture>& textures);
        ~Cell();
        void setSprite(int type);
        void setPosition(sf::Vector2f pos);
        void deleteCell();
    };

#endif