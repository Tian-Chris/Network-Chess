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
}

Entity::Entity(const std::string& spriteFileName, sf::Vector2f pos, int x, int y, const std::string& name) : 
    //not concatonated remember to add images/ elsewhere
    spriteTexture(spriteFileName),
    sprite(spriteTexture),
    hp(-1),
    x(x),
    y(y),
    name(name)
{
    setColor();
    sprite.setPosition(pos);
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

bool Entity::checkClick(sf::Vector2f mousePos) {
    if (mousePos.x > sprite.getPosition().x && mousePos.x < (sprite.getPosition().x + gridSize)) {
        if (mousePos.y > sprite.getPosition().y && mousePos.y < (sprite.getPosition().y + gridSize)) {
            std::cout << "Entity clicked: " << getName() << std::endl;
            std::cout << "mousepos:" << mousePos.x << " " << mousePos.y << std::endl;
            std::cout << "sprite:" << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            return true;
        }
    }
    else {
        return false;
    }   
}

void Entity::setColor() {
    if (name == "WP") {
        color = true;
    } else if (name == "WN") {
        color = true;
    } else if (name == "WB") {
        color = true;
    } else if (name == "WR") {
        color = true;
    } else if (name == "WQ") {
        color = true;
    } else if (name == "WK") {
        color = true;
    } else if (name == "BP") {
        color = false;
    } else if (name == "BN") {
        color = false;
    } else if (name == "BB") {
        color = false;
    } else if (name == "BR") {
        color = false;
    } else if (name == "BQ") {
        color = false;
    } else if (name == "BK") {
        color = false;
    }
}

void Entity::setX(int newX) { 
    x = newX; 
    setSpritePosition();
}
void Entity::setY(int newY) { 
    y = newY; 
    setSpritePosition();
}
void Entity::setPosition(int newX, int newY) { 
    x = newX; 
    y = newY; 
    setSpritePosition();
}
void Entity::setSpritePosition() { 
    sprite.setPosition({x * 32.f, y * 32.f}); 
}

bool Entity::canMove(int x, int y) {
    return true;
}