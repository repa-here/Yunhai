#pragma once

#include "../Object.hpp"
#include <SFML/Graphics.hpp>

class GeneralObject : public Object
{
public:
    GeneralObject();

    void render(
        sf::RenderWindow& window,
        float playerX,
        float playerY,
        float playerAngle,
        float playerPitch
    );

protected:
    sf::Sprite sprite;
    sf::Texture texture;
};
