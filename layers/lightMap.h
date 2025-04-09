#ifndef LIGHT_H
#define LIGHT_H
#include "../global/pch.h"
#include "layer.h"
#include "../entities/entities.h"
#include "../input/playerInput.h"

class LightMap {
    public:
        LightMap(unsigned int width, unsigned int height);
        void drawSource(sf::Vector2f center, float intensity);
        void clear();
        sf::RenderTexture texture;
    };
#endif