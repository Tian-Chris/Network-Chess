#ifndef CELL_H
#define CELL_H

using namespace std;

class Cell {
    public:
        sf::Vector2f position;  // Position of the cell
        int brightness;
        int spriteType;  // Represents the type of sprite (or texture)
        sf::Sprite* sprite;
        std::unordered_map<int, sf::Texture>* myTexture;
    
        // Default constructor
        Cell();
    
        // Constructor with position and sprite type
        Cell(sf::Vector2f pos, int type, std::unordered_map<int, sf::Texture>* textures);
        ~Cell();
        void setSprite(int Type);
        void setPosition(sf::Vector2f pos);
        void deleteCell();
    };

#endif
