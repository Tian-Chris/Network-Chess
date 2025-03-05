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
        sf::Sprite sprite;
        sf::Vector2f position;
        int brightness;

        Cell(sf::Texture& texture, sf::Vector2f pos);
};



#endif // CELL_H
