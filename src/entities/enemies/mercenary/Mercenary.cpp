#include "Mercenary.h"

Mercenary::Mercenary(bool alive, Vector2 position, int frameSpeed)
    : Enemy(alive, position, frameSpeed, 
            alive ? "../assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet.png" 
                  : "../assets/textures/enemies/mercenary/MercenaryDeathSpriteSheet.png", 
            alive ? 9 : 4) {}