#pragma once

#include <SFML/Graphics.hpp>

class Ceiling {
public:
    static void render(
        sf::RenderWindow& window,
        float playerX,
        float playerY,
        float playerAngle,
        float horizon,
        int screenWidth,
        int screenHeight,
        float FOV,
        sf::Texture& ceilingTexture);
};
