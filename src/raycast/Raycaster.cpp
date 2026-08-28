#include "Raycaster.hpp"
#include "../maps/map00.hpp"
#include "ceiling/Ceiling.hpp"

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

    sf::Texture& wallTexture = textures.getWall();
    sf::Texture& floorTexture = textures.getFloor();

    sf::Image floorImage = floorTexture.copyToImage();

    // Camera pitch.
    float pitchOffset = playerPitch * 300.0f;
    float horizon = screenHeight / 2.0f + pitchOffset;

    // Render ceiling if enabled.
    if (renderCeilingToggle)
    {
        Ceiling::render(
            window,
            playerX,
            playerY,
            playerAngle,
            horizon,
            screenWidth,
            screenHeight,
            FOV,
            textures.getCeiling()
        );
    }

    // Store floor pixels.
    sf::VertexArray floor(sf::Points, screenWidth * screenHeight);
    int vertexIndex = 0;

    for (int x = 0; x < screenWidth; x++)
    {
        // Calculate ray angle.
        float cameraX = (2.0f * static_cast<float>(x) / static_cast<float>(screenWidth)) - 1.0f;
        float rayAngle = playerAngle + cameraX * (FOV / 2.0f);

        // Precompute fish-eye correction factor.
        float cosAngleDiff = std::cos(rayAngle - playerAngle);

        float rayDirX = std::cos(rayAngle);
        float rayDirY = std::sin(rayAngle);

        // Current map square player is in.
        int mapX = static_cast<int>(playerX);
        int mapY = static_cast<int>(playerY);

        // Length of ray from one x or y-side to next x or y-side.
        float deltaDistX = (rayDirX == 0.0f) ? 1e30f : std::abs(1.0f / rayDirX);
        float deltaDistY = (rayDirY == 0.0f) ? 1e30f : std::abs(1.0f / rayDirY);

        // Length of ray from current position to next x or y-side.
        float sideDistX;
        float sideDistY;

        // What direction to step in x or y-direction (either +1 or -1).
        int stepX;
        int stepY;

        // Calculate step and initial sideDist.
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (playerX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0f - playerX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (playerY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0f - playerY) * deltaDistY;
        }

        // Perform DDA step loop.
        int side = 0; // 0 for X-wall, 1 for Y-wall
        while (true)
        {
            // Jump to next map square, either in x-direction, or in y-direction.
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Check if ray left map bounds.
            if (mapX < 0 || mapX >= 10 || mapY < 0 || mapY >= 10)
            {
                break;
            }

            // Check if ray hit a wall.
            if (map[mapY][mapX] == 1)
            {
                break;
            }
        }

        // Calculate perpendicular distance to wall (prevents fisheye automatically).
        float perpWallDist;
        if (side == 0)
        {
            perpWallDist = (sideDistX - deltaDistX);
        }
        else
        {
            perpWallDist = (sideDistY - deltaDistY);
        }

        // Prevent division by zero.
        if (perpWallDist < 0.1f)
        {
            perpWallDist = 0.1f;
        }

        // Correct fish-eye distance for walls.
        float correctedDistance = perpWallDist * cosAngleDiff;

        // Calculate wall height.
        float wallHeight = screenHeight / correctedDistance;

        // Calculate wall position.
        float wallTop = horizon - wallHeight / 2.0f;
        float wallBottom = horizon + wallHeight / 2.0f;

        // Calculate exact wall collision point (X coordinate).
        float wallX;
        if (side == 0)
        {
            wallX = playerY + perpWallDist * rayDirY;
        }
        else
        {
            wallX = playerX + perpWallDist * rayDirX;
        }
        wallX -= std::floor(wallX);

        // Convert wall position to texture X.
        int textureX = static_cast<int>(wallX * static_cast<float>(wallTexture.getSize().x));

        // Flip texture coordinate for opposite sides.
        if ((side == 0 && rayDirX < 0) || (side == 1 && rayDirY > 0))
        {
            textureX = static_cast<int>(wallTexture.getSize().x) - textureX - 1;
        }

        int maxTexX = std::max(0, static_cast<int>(wallTexture.getSize().x) - 1);
        textureX = std::clamp(textureX, 0, maxTexX);

        // Draw wall texture.
        sf::Sprite wall(wallTexture);
        wall.setTextureRect({
            textureX,
            0,
            1,
            static_cast<int>(wallTexture.getSize().y)
            });

        wall.setScale(
            1.0f,
            wallHeight / static_cast<float>(wallTexture.getSize().y)
        );

        wall.setPosition(
            static_cast<float>(x),
            wallTop
        );

        window.draw(wall);

        // Floor starts below the wall.
        int floorStart = std::clamp(
            static_cast<int>(wallBottom),
            0,
            screenHeight - 1
        );

        for (int y = floorStart; y < screenHeight; y++)
        {
            if (vertexIndex >= static_cast<int>(floor.getVertexCount()))
            {
                break;
            }

            // Distance from the horizon.
            float row = static_cast<float>(y) - horizon;

            if (row <= 1.0f)
            {
                continue;
            }

            // Correct floor fish-eye distortion using cosAngleDiff.
            float floorDistance = (screenHeight / (2.0f * row)) / cosAngleDiff;

            // Prevent extremely large distances.
            if (floorDistance > 20.0f)
            {
                floorDistance = 20.0f;
            }

            // Find floor position in world.
            float floorWorldX = playerX + rayDirX * floorDistance;
            float floorWorldY = playerY + rayDirY * floorDistance;

            // Convert world position to texture position.
            int textureXFloor = static_cast<int>(floorWorldX * floorImage.getSize().x) % static_cast<int>(floorImage.getSize().x);
            int textureYFloor = static_cast<int>(floorWorldY * floorImage.getSize().y) % static_cast<int>(floorImage.getSize().y);

            // Handle negative world coordinates.
            if (textureXFloor < 0)
            {
                textureXFloor += floorImage.getSize().x;
            }
            if (textureYFloor < 0)
            {
                textureYFloor += floorImage.getSize().y;
            }

            // Get texture pixel.
            sf::Color pixel = floorImage.getPixel(textureXFloor, textureYFloor);

            // Add floor pixel.
            floor[vertexIndex].position = { static_cast<float>(x), static_cast<float>(y) };
            floor[vertexIndex].color = pixel;

            vertexIndex++;
        }
    }

    // Draw floor.
    window.draw(floor);
}