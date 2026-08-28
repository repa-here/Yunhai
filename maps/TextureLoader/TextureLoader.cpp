#include "TextureLoader.hpp"

// Loading the textures with `loadFromFile` > `file path`
TextureLoader::TextureLoader()
{
    wallTexture.loadFromFile("assets/test_textures/wooden_wall.jpg");
    floorTexture.loadFromFile("assets/test_textures/wooden_floor.jpg");
}

sf::Texture& TextureLoader::getWall()
{
    return wallTexture;
}

sf::Texture& TextureLoader::getFloor()
{
    return floorTexture;
}