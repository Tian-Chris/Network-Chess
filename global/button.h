#ifndef BUTTON_H
#define BUTTON_H
#include "pch.h"
#include <functional>


class Button {
public:
    Button(const char* normalStr, const char* clickedStr, std::string words, sf::Vector2f location);
    void checkClick(sf::Vector2i);
    void setState(bool);
    void setText(std::string);
    bool getVar();
    sf::Sprite* getSprite();
    sf::Text* getText();
    void draw(std::function<void(const sf::Drawable&, const sf::RenderStates&)> func);


private:
    sf::Texture textureN;
    sf::Texture textureC;
    sf::Sprite normal;
    sf::Sprite clicked;
    sf::Sprite* currentSpr;
    sf::Font font;
    sf::Text text;
    bool current;
};

#endif
