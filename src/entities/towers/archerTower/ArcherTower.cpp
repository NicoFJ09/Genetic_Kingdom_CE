#include "ArcherTower.h"

ArcherTower::ArcherTower(Vector2 position, int level)
    : Tower(position, level,
        "../assets/textures/towers/towersInMap/ArcherLvl1.png", // texture
        15,     // damage
        1.0,    // speed
        6,      // range in pixels
        12      // special attack regeneration time
    )
{
    towerType = "Archer Tower";
}


void ArcherTower::UpdateStats() {
    // Actualizar estadísticas según el nivel
    if (level == 1) {
        damage = 10;
        speed = 1.0;
        range = 6;
        spAttackRegenerationTime = 12;
        texturePath = "../assets/textures/towers/towersInMap/ArcherLvl1.png";
    } else if (level == 2) {
        damage = 15;
        speed = 1.2;
        range = 7;
        spAttackRegenerationTime = 10;
        texturePath = "../assets/textures/towers/towersInMap/ArcherLvl2.png";
    } else if (level == 3) {
        damage = 20;
        speed = 1.5;
        range = 8;
        spAttackRegenerationTime = 8;
        texturePath = "../assets/textures/towers/towersInMap/ArcherLvl3.png";
    }

    // Actualizar la textura usando LoadAndResizeTexture
    UnloadTexture(texture); // Liberar la textura anterior
    texture = LoadAndResizeTexture(texturePath, 32, 32);
}