#include "header/cell.h"
#include "header/pch.h"

Cell::Cell() : brightness(1), position(0.f, 0.f), spriteType(0) 
{
    sf::Sprite* sprite = nullptr;
    std::unordered_map<int, sf::Texture>* textures = nullptr;
}

Cell::Cell(sf::Vector2f pos, int type, std::unordered_map<int, sf::Texture>* textures)
    : position(pos), brightness(1), spriteType(type) {
    cout << "pos: " << pos.x << ", " << pos.y << '\n';
    cout << "spriteType: " << spriteType << '\n';



    // Ensure textures is not nullptr before accessing it
    if (textures != nullptr && textures->count(spriteType)) {
        // Create the sprite using the texture at spriteType
        sprite = new sf::Sprite((*textures)[spriteType]);
        sprite->setPosition(pos);
    } else {
        // Handle case where texture doesn't exist, if necessary
        sprite = nullptr;
    }
}

Cell::~Cell()
{
    delete sprite;
}

void Cell::changeSprite(int newType)
{
    delete sprite;
    sprite = new sf::Sprite((*textures)[spriteType]);
}