#include "TextureLoader.hpp"

// Loading the textures with `loadFromFile` > `file path`
TextureLoader::TextureLoader()
{
    wallTexture.loadFromFile("assets/test_textures/wall.png");
    floorTexture.loadFromFile("assets/test_textures/floor.png");
    ceilingTexture.loadFromFile("assets/test_textures/ceiling.png");
}

sf::Texture& TextureLoader::getWall()
{
    return wallTexture;
}

sf::Texture& TextureLoader::getFloor()
{
    return floorTexture;
}

sf::Texture& TextureLoader::getCeiling()
{
    return ceilingTexture;
}