#include "MageTower.h"

MageTower::MageTower(Vector2 position, int level)
    : Tower(position, level,
        "../assets/textures/towers/towersInMap/MageLvl1.png", // texture
        30,   // damage
        1,    // speed
        4,   // range in pixels
        8    // special attack regeneration time
    )
{
    towerType = "Mage Tower";
}

void MageTower::UpdateStats() {
    // Actualizar estadísticas según el nivel
    if (level == 1) {
        damage = 30;
        speed = 1;
        range = 4;
        spAttackRegenerationTime = 8;
        texturePath = "../assets/textures/towers/towersInMap/MageLvl1.png";
    } else if (level == 2) {
        damage = 40;
        speed = 1.1;
        range = 5;
        spAttackRegenerationTime = 7;
        texturePath = "../assets/textures/towers/towersInMap/MageLvl2.png";
    } else if (level == 3) {
        damage = 50;
        speed = 1.2;
        range = 6;
        spAttackRegenerationTime = 5;
        texturePath = "../assets/textures/towers/towersInMap/MageLvl3.png";
    }

    // Actualizar la textura usando LoadAndResizeTexture
    UnloadTexture(texture); // Liberar la textura anterior
    texture = LoadAndResizeTexture(texturePath, 32, 32);
}