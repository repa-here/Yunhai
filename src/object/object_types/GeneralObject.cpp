#include "GeneralObject.hpp"

#include <cmath>

GeneralObject::GeneralObject()
{
    type = Type::General;
}

void GeneralObject::render(
    sf::RenderWindow& window,
    float playerX,
    float playerY,
    float playerAngle,
    float playerPitch
)
{
    const float screenWidth = 800.0f;
    const float screenHeight = 600.0f;
    const float FOV = 1.0472f;

    // Position relative to player.
    float relativeX = posX - playerX;
    float relativeY = posY - playerY;

    // Rotate world relative to camera.
    float sinAngle = std::sin(-playerAngle);
    float cosAngle = std::cos(-playerAngle);

    float cameraX =
        relativeX * cosAngle -
        relativeY * sinAngle;

    float cameraY =
        relativeX * sinAngle +
        relativeY * cosAngle;

    // Object is behind the player.
    if (cameraX <= 0.1f)
    {
        return;
    }

    // Calculate focal length.
    float focalLength =
        (screenWidth / 2.0f) /
        std::tan(FOV / 2.0f);

    // Convert world position to screen position.
    float screenX =
        screenWidth / 2.0f +
        (cameraY / cameraX) * focalLength;

    // Calculate size based on distance.
    float objectHeight =
        (screenHeight / cameraX) * scale;

    float objectWidth =
        objectHeight;

    // Apply camera pitch.
    float pitchOffset =
        playerPitch * 300.0f;

    float screenY =
        screenHeight / 2.0f +
        pitchOffset -
        objectHeight / 2.0f;

    // Position sprite.
    sprite.setPosition(
        screenX - objectWidth / 2.0f,
        screenY
    );

    // Scale sprite according to distance.
    if (sprite.getTexture())
    {
        float textureWidth =
            static_cast<float>(
                sprite.getTexture()->getSize().x
                );

        float textureHeight =
            static_cast<float>(
                sprite.getTexture()->getSize().y
                );

        sprite.setScale(
            objectWidth / textureWidth,
            objectHeight / textureHeight
        );
    }

    window.draw(sprite);
}
