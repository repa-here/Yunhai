#pragma once

#include <SFML/Graphics.hpp>

#include "../maps/TextureLoader/TextureLoader.hpp"

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

private:
    TextureLoader textures;
};