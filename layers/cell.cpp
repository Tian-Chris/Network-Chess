#include "cell.h"

Cell::Cell() : brightness(1), position(0.f, 0.f), spriteType(0), sprite(nullptr), myTexture(nullptr)
{
    // Default constructor
}

Cell::Cell(sf::Vector2f pos, int type, std::unordered_map<int, sf::Texture>& textures)
    : position(pos), brightness(1), spriteType(type), myTexture(&textures) {
    //cout << "pos: " << pos.x << ", " << pos.y << '\n';
    //cout << "spriteType: " << spriteType << '\n';

    // Ensure textures is not nullptr before accessing it
    if (myTexture != nullptr && myTexture->count(spriteType)) {
        // Create the sprite using the texture at spriteType
        setSprite(spriteType);
        setPosition(pos);
    } else {
        // Handle case where texture doesn't exist, if necessary
        sprite = nullptr;
    }
}


Cell::~Cell()
{
    sprite.reset();
}

void Cell::setSprite(int type)
{
    if(sprite == nullptr)
    {
        sprite = std::make_unique<sf::Sprite>((*myTexture)[type]);
    }
    else
    {
        sprite.reset();
        sprite = std::make_unique<sf::Sprite>((*myTexture)[type]);
    }
}
void Cell::setPosition(sf::Vector2f pos)
{
    sprite -> setPosition(pos);
}

void Cell::deleteCell() 
{
    sprite.reset();
}