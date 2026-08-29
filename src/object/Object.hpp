#pragma once

class Object
{
public:

    // Object Types:

    // General - Decorative objects
    // Lighting - Objects that act as a light source
    // Collectible - Objects meant to be collected (such as ammo, health, currency, etc.)

    enum class Type
    {
        General,
        Lighting,
        Collectible
    };

    // Object variables
    Type type = Type::General;

    float posX = 2.5f;
    float posY = 2.5f;
        
    // 1 = default size
    float scale = 1.0f;
};
