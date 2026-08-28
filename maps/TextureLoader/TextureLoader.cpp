#include "TextureLoader.hpp"

// Loading the textures with `loadFromFile` > `file path`
TextureLoader::TextureLoader()
{
    wallTexture.loadFromFile("assets/test_textures/wall.png");
    floorTexture.loadFromFile("assets/test_textures/floor.png");
}

sf::Texture& TextureLoader::getWall()
{
    return wallTexture;
}

sf::Texture& TextureLoader::getFloor()
{
    return floorTexture;
}