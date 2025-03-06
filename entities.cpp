#include "header/entities.h"
#include "header/pch.h"

Entity::Entity(std::string& spriteFileName, int hitPoints, sf::Vector2f pos) : 
    //not concatonated remember to add images/ elsewhere
    spriteTexture(spriteFileName),
    sprite(spriteTexture),
    hp(hitPoints)
{
    sprite.setPosition(pos);   
}

void Entity::draw() {

}

void Entity::move(char input)
{
    //size of movement = 50 did not know how to do this better manually set it to 50
    switch(input) {
        case 'w':
            sprite.move({0.f, -50.f});
            break;
        case 'a':
            sprite.move({-50.f, 0.f});
            break;
        case 's':
            sprite.move({0.f, 50.f});
            break;
        case 'd':
            sprite.move({50.f, 0.f});
            break;
    }
}