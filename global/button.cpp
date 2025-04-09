#include "button.h"
#include <functional>

Button::Button(const char* normalStr, const char* clickedStr, std::string words, sf::Vector2f location)
    : textureN(normalStr),
      textureC(clickedStr),
      normal(textureN),
      clicked(textureC),
      font("text/Arial.ttf"),
      text(font) 
{
    this->currentSpr = &this->normal;
    current = false;
    this->normal.setPosition(location);
    this->clicked.setPosition(location);
    text.setString(words);  // Set the text string
    text.setCharacterSize(20);  // Set the text size
    text.setFillColor(sf::Color::White);  // Set the text color
    text.setPosition(location);  // Set position in the window
}

void Button::checkClick(sf::Vector2i mousePos) {
    if (mousePos.x > currentSpr->getPosition().x && mousePos.x < (currentSpr->getPosition().x + textureN.getSize().x)) {
        if (mousePos.y > currentSpr->getPosition().y && mousePos.y < (currentSpr->getPosition().y + textureN.getSize().y)) {
            setState(!current);
        }
    }
}

void Button::setState(bool which) {
    current = which;
    if (current) {
        currentSpr = &clicked;
        return;
    }
    currentSpr = &normal;
}

void Button::setText(std::string words) {
}

bool Button::getVar() {
    return current;
}

sf::Sprite* Button::getSprite() {
    return currentSpr;
}

sf::Text* Button::getText() {
    return &text;
}

void Button::draw(std::function<void(const sf::Drawable&, const sf::RenderStates&)> func) {
    func(*currentSpr, sf::RenderStates::Default);
    func(text, sf::RenderStates::Default);
}