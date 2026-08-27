#include "Player.hpp"
#include "../maps/map00.hpp"

#include <cmath>
#include <SFML/Window/Keyboard.hpp>

void Player::movement_update()
{
    float newX = posX;
    float newY = posY;

    // Move forward.
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::W))
    {
        newX += std::cos(angle) * speed;
        newY += std::sin(angle) * speed;
    }

    // Move backward.
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::S))
    {
        newX -= std::cos(angle) * speed;
        newY -= std::sin(angle) * speed;
    }

    // Strafe left.
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::A))
    {
        newX += std::cos(angle - 1.5708f) * speed;
        newY += std::sin(angle - 1.5708f) * speed;
    }

    // Strafe right.
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::D))
    {
        newX += std::cos(angle + 1.5708f) * speed;
        newY += std::sin(angle + 1.5708f) * speed;
    }

    // Check collision.
    int mapX = static_cast<int>(newX);
    int mapY = static_cast<int>(newY);

    if (mapX >= 0 && mapX < 10 &&
        mapY >= 0 && mapY < 10 &&
        map[mapY][mapX] != 1)
    {
        posX = newX;
        posY = newY;
    }
}

void Player::mouse_update(float mouseDeltaX, float mouseDeltaY)
{
    angle += mouseDeltaX * mouseSensitivity;
    pitch -= mouseDeltaY * mouseSensitivity;

    // Limit looking up/down.
    if (pitch > 1.2f)
        pitch = 1.2f;

    if (pitch < -1.2f)
        pitch = -1.2f;
}