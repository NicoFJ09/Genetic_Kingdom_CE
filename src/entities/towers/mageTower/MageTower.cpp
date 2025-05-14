#include "MageTower.h"

MageTower::MageTower(Vector2 position, int level)
    : Tower(position, level,
        level == 1 ? "../assets/textures/towers/towersInMap/MageLvl1.png" :
        level == 2 ? "../assets/textures/towers/towersInMap/MageLvl2.png" :
                     "../assets/textures/towers/towersInMap/MageLvl3.png",
        level == 1 ? 12 : level == 2 ? 18 : 25,           // damage
        level == 1 ? 1  : level == 2 ? 2  : 3,            // speed
        level == 1 ? 70 : level == 2 ? 140 : 210,        // range in pixels
        level == 1 ? 60 : level == 2 ? 45 : 30          // special attack regen
    ){
    towerType = "Mage Tower";
}

void MageTower::UpdateStats() {
    // Actualizar estadísticas según el nivel
    if (level == 1) {
        damage = 12;
        speed = 1;
        range = 70;
        spAttackRegenerationTime = 60;
        texturePath = "../assets/textures/towers/towersInMap/MageLvl1.png";
    } else if (level == 2) {
        damage = 18;
        speed = 2;
        range = 140;
        spAttackRegenerationTime = 45;
        texturePath = "../assets/textures/towers/towersInMap/MageLvl2.png";
    } else if (level == 3) {
        damage = 25;
        speed = 3;
        range = 210;
        spAttackRegenerationTime = 30;
        texturePath = "../assets/textures/towers/towersInMap/MageLvl3.png";
    }

    // Actualizar la textura usando LoadAndResizeTexture
    UnloadTexture(texture); // Liberar la textura anterior
    texture = LoadAndResizeTexture(texturePath, 32, 32);
}