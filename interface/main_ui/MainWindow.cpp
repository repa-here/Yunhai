#include <SFML/Graphics.hpp>

#include "MainWindow.hpp"
#include "../player/Player.hpp"
#include "../raycast/Raycaster.hpp"

void MainWindow()
{
    Player player;
    Raycaster raycaster;

    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Yunhai Engine"
    );

    // Get the center of the window.
    const float centerX =
        window.getSize().x / 2.0f;

    const float centerY =
        window.getSize().y / 2.0f;

    // Center the mouse.
    sf::Mouse::setPosition(
        {
            static_cast<int>(centerX),
            static_cast<int>(centerY)
        },
        window
    );

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Update player movement.
        player.movement_update();

        // Get mouse movement.
        sf::Vector2i mousePosition =
            sf::Mouse::getPosition(window);

        float mouseDeltaX =
            mousePosition.x - centerX;

        float mouseDeltaY =
            mousePosition.y - centerY;

        // Update player rotation.
        player.mouse_update(
            mouseDeltaX,
            mouseDeltaY
        );

        // Reset mouse to center.
        sf::Mouse::setPosition(
            {
                static_cast<int>(centerX),
                static_cast<int>(centerY)
            },
            window
        );

        // Clear previous frame.
        window.clear();

        // Render the 3D world.
        raycaster.render(
            window,
            player.posX,
            player.posY,
            player.angle,
            player.pitch
        );

        window.display();
    }
}