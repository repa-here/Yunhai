#pragma once

#include <SFML/Graphics.hpp>

// Part of the texture loader is also in the raycaster codes.

class TextureLoader {
public:
	TextureLoader();

	sf::Texture& getWall();
	sf::Texture& getFloor();
	sf::Texture& getCeiling();

private:
	// Texture Variables
	sf::Texture wallTexture;
	sf::Texture floorTexture;
	sf::Texture ceilingTexture;
};