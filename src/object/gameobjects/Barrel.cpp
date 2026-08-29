#include "Barrel.hpp"

Barrel::Barrel()
{
    texture.loadFromFile(
        "assets/test_textures/object_textures/barrel_object.png"
    );

    sprite.setTexture(texture);
}
