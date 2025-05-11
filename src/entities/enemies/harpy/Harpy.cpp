#include "Harpy.h"

Harpy::Harpy(bool alive, Vector2 position, int frameSpeed)
    : Enemy(alive, position, frameSpeed, 
            alive ? "../assets/textures/enemies/harpy/HarpyMoveSpriteSheet.png" 
                  : "../assets/textures/enemies/harpy/HarpyDeathSpriteSheet.png", 
            alive ? 23 : 7) {}