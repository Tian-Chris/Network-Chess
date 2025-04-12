#ifndef ENTITIES_H
#define ENTITIES_H
#include "../global/pch.h"

class Entity {
public:
    Entity(const std::string& spriteFileName);
    Entity(const std::string& spriteFileName, int hitPoints, sf::Vector2f pos);
    sf::Texture spriteTexture;
    sf::Sprite sprite;

    int getX();
    int getY();
    void setName(const std::string& newName) { name = newName; };
    std::string getName() const { return name; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }

    //empty
    void draw();
    void move(char input);
    void reset(const std::string& filename);
    void checkClick(sf::Vector2i);
    void setState();

private:
    int hp;
    int x;
    int y;
    bool clicked;
    std::string name;
};

#endif