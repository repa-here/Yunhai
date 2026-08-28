// Ceiling Separation Explained:
// In the future editor, the ceiling will be toggled `off` and `on` based on your preference.
// When the ceiling is turned `off`, it will unlock a new option: `skybox`.

#include "Ceiling.hpp"
#include <cmath>
#include <algorithm>

void Ceiling::render(
    sf::RenderWindow& window,
    float playerX,
    float playerY,
    float playerAngle,
    float horizon,
    int screenWidth,
    int screenHeight,
    float FOV,
    sf::Texture& ceilingTexture)
{
    sf::Image ceilingImage = ceilingTexture.copyToImage();

    sf::VertexArray ceiling(sf::Points, screenWidth * screenHeight);
    int vertexIndex = 0;

    int ceilingEnd = std::clamp(static_cast<int>(horizon), 0, screenHeight);

    for (int x = 0; x < screenWidth; x++)
    {
        float cameraX = (2.0f * static_cast<float>(x) / static_cast<float>(screenWidth)) - 1.0f;
        float rayAngle = playerAngle + cameraX * (FOV / 2.0f);
        float cosAngleDiff = std::cos(rayAngle - playerAngle);

        float rayDirX = std::cos(rayAngle);
        float rayDirY = std::sin(rayAngle);

        for (int y = 0; y < ceilingEnd; y++)
        {
            if (vertexIndex >= static_cast<int>(ceiling.getVertexCount()))
            {
                break;
            }

            // Distance above the horizon
            float row = horizon - static_cast<float>(y);

            if (row <= 1.0f)
            {
                continue;
            }

            // Correct ceiling fish-eye distortion
            float ceilingDistance = (screenHeight / (2.0f * row)) / cosAngleDiff;

            if (ceilingDistance > 20.0f)
            {
                ceilingDistance = 20.0f;
            }

            // Find ceiling position in world
            float ceilingWorldX = playerX + rayDirX * ceilingDistance;
            float ceilingWorldY = playerY + rayDirY * ceilingDistance;

            // Convert world position to texture coordinates
            int textureXCeiling = static_cast<int>(ceilingWorldX * ceilingImage.getSize().x) % static_cast<int>(ceilingImage.getSize().x);
            int textureYCeiling = static_cast<int>(ceilingWorldY * ceilingImage.getSize().y) % static_cast<int>(ceilingImage.getSize().y);

            // Handle negative world coordinates
            if (textureXCeiling < 0)
            {
                textureXCeiling += ceilingImage.getSize().x;
            }
            if (textureYCeiling < 0)
            {
                textureYCeiling += ceilingImage.getSize().y;
            }

            // Sample texture pixel
            sf::Color pixel = ceilingImage.getPixel(textureXCeiling, textureYCeiling);

            ceiling[vertexIndex].position = { static_cast<float>(x), static_cast<float>(y) };
            ceiling[vertexIndex].color = pixel;

            vertexIndex++;
        }
    }

    // Draw ceiling
    window.draw(ceiling);
}
