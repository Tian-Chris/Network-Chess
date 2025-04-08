#include "lightMap.h"


LightMap::LightMap(unsigned int width, unsigned int height)
{
    texture.resize({width, height});
    texture.clear(sf::Color::Black);

}

void LightMap::drawSource(sf::Vector2f center, float intensity)
{
    clear();
    const int segments = 30;  // More segments = smoother circle
    float radius = intensity;
    sf::VertexArray circle(sf::PrimitiveType::TriangleFan, segments + 2);
    circle[0].position = center;
    circle[0].color = sf::Color(255, 255, 255, 255);
    for (int i = 1; i <= segments + 1; i++) {
        float angle = i * 2 * 3.14159265f / segments;
        circle[i].position = center + sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius);
        circle[i].color = sf::Color(255, 255, 200, 0); // Soft fade at edges
    }
    texture.draw(circle, sf::BlendAdd); 
    texture.display();
}

void LightMap::clear()
{
    texture.clear(sf::Color::Black);
}

    