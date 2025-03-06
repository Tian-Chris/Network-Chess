#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "cell.h"

class Layer {
public:
    Layer(const std::string& fileName, float gridSize);
    void draw(sf::RenderWindow& window);

private:
    void loadFromFile(const std::string& fileName);
    void createSprites();

    std::vector<std::vector<Cell>> grid;
    std::vector<sf::Sprite> sprites;
    std::unordered_map<int, sf::Texture> textures;  // Map texture IDs to textures

    //pixel width of each grid
    float gridSize;
};

#endif