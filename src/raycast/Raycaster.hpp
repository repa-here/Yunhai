#pragma once

#include <SFML/Graphics.hpp>

class Raycaster
{
public:
    void render(
        sf::RenderWindow& window,
        float playerX,
        float playerY,
        float playerAngle,
        float playerPitch
    );
};