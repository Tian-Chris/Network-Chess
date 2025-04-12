#include "entities.h"
#include "../global/globals.h"

Entity::Entity(const std::string& spriteFileName) : 
    //not concatonated remember to add images/ elsewhere
    spriteTexture(spriteFileName),
    sprite(spriteTexture),
    hp(-1)
{
    sprite.setPosition({0.f, 0.f});
    x = 0;
    y = 0;
    clicked = false;
}

Entity::Entity(const std::string& spriteFileName, int hitPoints, sf::Vector2f pos) : 
    //not concatonated remember to add images/ elsewhere
    spriteTexture(spriteFileName),
    sprite(spriteTexture),
    hp(hitPoints)
{
    sprite.setPosition(pos);
    x = pos.x/gridSize;
    y = pos.y/gridSize;
    clicked = false;
}

//empty
void Entity::draw() {

}

void Entity::reset(const std::string& filename) {
    spriteTexture.loadFromFile(filename);
    sprite.setTexture(spriteTexture);
}

void Entity::move(char input)
{
    //size of movement = 50 did not know how to do this better manually set it to 50 manually set gridspace
    switch(input) {
        case 'w':
            sprite.move({0.f, -gridSize});
            y--;
            break;
        case 'a':
            sprite.move({-gridSize, 0.f});
            x--;
            break;
        case 's':
            sprite.move({0.f, gridSize});
            y++;
            break;
        case 'd':
            sprite.move({gridSize, 0.f});
            x++;
            break;
    }
}

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}

void Entity::checkClick(sf::Vector2i mousePos) {
    if (mousePos.x > sprite.getPosition().x && mousePos.x < (sprite.getPosition().x + gridSize)) {
        if (mousePos.y > sprite.getPosition().y && mousePos.y < (sprite.getPosition().y + gridSize)) {

            setState();
        }
    }
}
void Entity::setState() {
    clicked = !clicked;
}