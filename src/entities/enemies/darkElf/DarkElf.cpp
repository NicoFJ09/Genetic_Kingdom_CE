#include "DarkElf.h"

DarkElf::DarkElf(bool alive, Vector2 position, int frameSpeed)
    : Enemy(alive, position, frameSpeed, 
            alive ? "../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet.png" 
                  : "../assets/textures/enemies/darkelf/DarkElfDeathSpriteSheet.png", 
            alive ? 8 : 7) {}