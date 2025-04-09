#ifndef ENTITIES_H
#define ENTITIES_H
#include "../global/pch.h"

class Entity {
public:
    Entity(const std::string& spriteFileName, int hitPoints, sf::Vector2f pos);
    sf::Texture spriteTexture;
    sf::Sprite sprite;
    int hp;
    int x;
    int y;
    int getX();
    int getY();

    //empty
    void draw();
    void move(char input);
    void reset(const std::string& filename);

private:
};

#endif