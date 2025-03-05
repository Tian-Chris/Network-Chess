#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>

using namespace std;

class Cell {
    public:
        sf::Vector2f position;  // Position of the cell
        int brightness;
        int spriteType;  // Represents the type of sprite (or texture)
    
        // Default constructor
        Cell();
    
        // Constructor with position and sprite type
        Cell(sf::Vector2f pos, int type);
    };

#endif // CELL_H
