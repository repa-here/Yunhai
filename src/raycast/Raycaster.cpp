#include "Raycaster.hpp"
#include "../maps/map00.hpp"

#include <cmath>
#include <algorithm>

void Raycaster::render(
    sf::RenderWindow& window,
    float playerX,
    float playerY,
    float playerAngle,
    float playerPitch)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    const float FOV = 1.0472f;
    const float rayStep = 0.01f;

    sf::Texture& wallTexture = textures.getWall();
    sf::Texture& floorTexture = textures.getFloor();

    sf::Image floorImage = floorTexture.copyToImage();

    // Camera pitch.
    float pitchOffset =
        playerPitch * 300.0f;

    float horizon =
        screenHeight / 2.0f +
        pitchOffset;

    // Store floor pixels.
    sf::VertexArray floor(
        sf::Points,
        screenWidth * screenHeight
    );

    int vertexIndex = 0;

    for (int x = 0; x < screenWidth; x++)
    {
        // Calculate ray angle.
        float cameraX =
            (2.0f * x / screenWidth) - 1.0f;

        float rayAngle =
            playerAngle +
            cameraX * (FOV / 2.0f);

        // Ray starts at player.
        float rayX = playerX;
        float rayY = playerY;

        float rayDirX =
            std::cos(rayAngle);

        float rayDirY =
            std::sin(rayAngle);

        float distance = 0.0f;

        // Move ray until it hits a wall.
        while (true)
        {
            rayX += rayDirX * rayStep;
            rayY += rayDirY * rayStep;

            distance += rayStep;

            int mapX =
                static_cast<int>(rayX);

            int mapY =
                static_cast<int>(rayY);

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
            distance *
            std::cos(rayAngle - playerAngle);

        // Calculate wall height.
        float wallHeight =
            screenHeight /
            correctedDistance;

        // Calculate wall position.
        float wallTop =
            horizon -
            wallHeight / 2.0f;

        float wallBottom =
            horizon +
            wallHeight / 2.0f;

        // Find where the ray hit the wall.
        float xFraction =
            rayX - std::floor(rayX);

        float yFraction =
            rayY - std::floor(rayY);

        float wallX;

        if (xFraction < 0.05f ||
            xFraction > 0.95f)
        {
            wallX = yFraction;
        }
        else
        {
            wallX = xFraction;
        }

        // Convert wall position to texture X.
        int textureX =
            static_cast<int>(
                wallX *
                wallTexture.getSize().x
                );

        textureX =
            std::clamp(
                textureX,
                0,
                static_cast<int>(
                    wallTexture.getSize().x - 1
                    )
            );

        // Draw wall texture.
        sf::Sprite wall(wallTexture);

        wall.setTextureRect({
            textureX,
            0,
            1,
            static_cast<int>(
                wallTexture.getSize().y
            )
            });

        wall.setScale(
            1.0f,
            wallHeight /
            wallTexture.getSize().y
        );

        wall.setPosition(
            static_cast<float>(x),
            wallTop
        );

        window.draw(wall);

        // Floor starts below the wall.
        int floorStart =
            std::clamp(
                static_cast<int>(wallBottom),
                0,
                screenHeight - 1
            );

        for (int y = floorStart;
            y < screenHeight;
            y++)
        {
            if (vertexIndex >=
                static_cast<int>(
                    floor.getVertexCount()
                    ))
            {
                break;
            }

            // Distance from the horizon.
            float row =
                static_cast<float>(y) -
                horizon;

            if (row <= 1.0f)
            {
                continue;
            }

            // Calculate floor distance.
            float floorDistance =
                screenHeight /
                (2.0f * row);

            // Prevent extremely large distances.
            if (floorDistance > 20.0f)
            {
                floorDistance = 20.0f;
            }

            // Find floor position in world.
            float floorWorldX =
                playerX +
                rayDirX *
                floorDistance;

            float floorWorldY =
                playerY +
                rayDirY *
                floorDistance;

            // Convert world position to texture position.
            int textureXFloor =
                static_cast<int>(
                    floorWorldX *
                    floorImage.getSize().x
                    ) %
                static_cast<int>(
                    floorImage.getSize().x
                    );

            int textureYFloor =
                static_cast<int>(
                    floorWorldY *
                    floorImage.getSize().y
                    ) %
                static_cast<int>(
                    floorImage.getSize().y
                    );

            // Handle negative world coordinates.
            if (textureXFloor < 0)
            {
                textureXFloor +=
                    floorImage.getSize().x;
            }

            if (textureYFloor < 0)
            {
                textureYFloor +=
                    floorImage.getSize().y;
            }

            // Get texture pixel.
            sf::Color pixel =
                floorImage.getPixel(
                    textureXFloor,
                    textureYFloor
                );

            // Add floor pixel.
            floor[vertexIndex].position = {
                static_cast<float>(x),
                static_cast<float>(y)
            };

            floor[vertexIndex].color =
                pixel;

            vertexIndex++;
        }
    }

    // Draw floor.
    window.draw(floor);
}