#ifndef ENTITIES_H
#define ENTITIES_H

class Entity {
public:
    Entity(const std::string& spriteFileName, int hitPoints, sf::Vector2f pos);
    sf::Texture spriteTexture;
    sf::Sprite sprite;
    int hp;
    int x;
    int y;

    //empty
    void draw();
    void move(char input);
};

#endif