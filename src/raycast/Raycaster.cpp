#include "Raycaster.hpp"
#include "../maps/map00.hpp"

#include <cmath>

void Raycaster::render(
    sf::RenderWindow& window,
    float playerX,
    float playerY,
    float playerAngle,
    float playerPitch)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    const float FOV = 1.0472f; // 60 degrees
    const float rayStep = 0.01f;

    for (int x = 0; x < screenWidth; x++)
    {
        // Calculate ray angle.
        float cameraX =
            (2.0f * x / screenWidth) - 1.0f;

        float rayAngle =
            playerAngle + cameraX * (FOV / 2.0f);

        // Ray starts at the player.
        float rayX = playerX;
        float rayY = playerY;

        float rayDirX = std::cos(rayAngle);
        float rayDirY = std::sin(rayAngle);

        float distance = 0.0f;

        // Move ray until it hits a wall.
        while (true)
        {
            rayX += rayDirX * rayStep;
            rayY += rayDirY * rayStep;

            distance += rayStep;

            int mapX = static_cast<int>(rayX);
            int mapY = static_cast<int>(rayY);

            // Stop if ray leaves the map.
            if (mapX < 0 || mapX >= 10 ||
                mapY < 0 || mapY >= 10)
            {
                break;
            }

            // Stop when ray hits a wall.
            if (map[mapY][mapX] == 1)
            {
                break;
            }
        }

        // Prevent division by zero.
        if (distance < 0.1f)
        {
            distance = 0.1f;
        }

        // Correct fish-eye distortion.
        float correctedDistance =
            distance * std::cos(rayAngle - playerAngle);

        // Calculate wall height.
        float pitchOffset = playerPitch * 300.0f;

        float wallHeight =
            screenHeight / correctedDistance;

        float wallTop =
            (screenHeight - wallHeight) / 2.0f + pitchOffset;

        float wallBottom =
            (screenHeight + wallHeight) / 2.0f + pitchOffset;

        // Draw wall column.
        sf::VertexArray wall(sf::Lines, 2);

        wall[0].position = {
            static_cast<float>(x),
            wallTop
        };

        wall[1].position = {
            static_cast<float>(x),
            wallBottom
        };

        window.draw(wall);
    }
}