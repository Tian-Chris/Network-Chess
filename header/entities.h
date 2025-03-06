#ifndef ENTITIES_H
#define ENTITIES_H

class Entity {
public:
    Entity(std::string& spriteFileName, int hitPoints, sf::Vector2f pos);
    sf::Texture spriteTexture;
    sf::Sprite sprite;
    int hp;

    void Entity::draw();
    void Entity::move(char input);
};

#endif