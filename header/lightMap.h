#ifndef LIGHT_H
#define LIGHT_H
#include "pch.h"
#include "layer.h"
#include "entities.h"
#include "playerInput.h"

class LightMap {
    public:
        LightMap(unsigned int width, unsigned int height);
        void drawSource(sf::Vector2f center, float intensity);
        void clear();
        sf::RenderTexture texture;
    };
#endif