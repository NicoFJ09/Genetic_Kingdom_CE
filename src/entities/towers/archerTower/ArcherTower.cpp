
#include "ArcherTower.h"

ArcherTower::ArcherTower(Vector2 position, int level)
    : Tower(position, level,
        level == 1 ? "assets/textures/towers/towersInMap/ArcherLvl1.png" :
        level == 2 ? "assets/textures/towers/towersInMap/ArcherLvl2.png" :
                     "assets/textures/towers/towersInMap/ArcherLvl3.png",
        level == 1 ? 10 : level == 2 ? 15 : 20,           // damage
        level == 1 ? 2  : level == 2 ? 3  : 4,            // speed
        level == 1 ? 64 : level == 2 ? 128 : 192,        // range in pixels
        level == 1 ? 10 : level == 2 ? 5 : 3,           // attack regen
        level == 1 ? 50 : level == 2 ? 40 : 25          // special attack regen
    )
{}
