#ifndef ENTITIES_H
#define ENTITIES_H
#include "../global/pch.h"
#include "../game/chessLogic.h"


class Entity {
public:
    Entity(const std::string& spriteFileName);
    Entity(const std::string& spriteFileName, int hitPoints, sf::Vector2f pos);
    Entity(const std::string& spriteFileName, sf::Vector2f pos, int x, int y, const std::string& name);
    sf::Texture spriteTexture;
    sf::Sprite sprite;

    int getX() const;
    int getY() const;
    void setName(const std::string& newName) { name = newName; };
    std::string getName() const { return name; }
    void setType();
    int getType() const { return type; }
    void setPosition(int newX, int newY);
    void setSpritePosition();
    void setX(int newX);
    void setY(int newY);

    //empty
    void draw();
    void move(char input);
    void reset(const std::string& filename);
    bool checkClick(sf::Vector2f);
    bool getColor() const { return color; }
    void setColor();

    bool canMove(int x, int y);

private:
    int hp;
    int x;
    int y;
    bool color;
    std::string name;
    int type;
};

#endif