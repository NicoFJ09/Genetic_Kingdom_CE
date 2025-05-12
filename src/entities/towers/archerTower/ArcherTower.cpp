#include "ArcherTower.h"

ArcherTower::ArcherTower(Vector2 position, int level)
    : Tower(position, level,
        level == 1 ? "../assets/textures/towers/towersInMap/ArcherLvl1.png" :
        level == 2 ? "../assets/textures/towers/towersInMap/ArcherLvl2.png" :
                     "../assets/textures/towers/towersInMap/ArcherLvl3.png",
        level == 1 ? 10 : level == 2 ? 15 : 20,           // damage
        level == 1 ? 2  : level == 2 ? 3  : 4,            // speed
        level == 1 ? 64 : level == 2 ? 128 : 192,        // range in pixels
        level == 1 ? 10 : level == 2 ? 5 : 3,           // attack regen
        level == 1 ? 50 : level == 2 ? 40 : 25          // special attack regen
    ){
    towerType = "Archer Tower";
}

void ArcherTower::UpdateStats() {
    // Actualizar estadísticas según el nivel
    if (level == 1) {
        damage = 10;
        speed = 2;
        range = 64;
        attackRegenerationTime = 10;
        spAttackRegenerationTime = 50;
        texturePath = "../assets/textures/towers/towersInMap/ArcherLvl1.png";
    } else if (level == 2) {
        damage = 15;
        speed = 3;
        range = 128;
        attackRegenerationTime = 5;
        spAttackRegenerationTime = 40;
        texturePath = "../assets/textures/towers/towersInMap/ArcherLvl2.png";
    } else if (level == 3) {
        damage = 20;
        speed = 4;
        range = 192;
        attackRegenerationTime = 3;
        spAttackRegenerationTime = 25;
        texturePath = "../assets/textures/towers/towersInMap/ArcherLvl3.png";
    }

    // Actualizar la textura usando LoadAndResizeTexture
    UnloadTexture(texture); // Liberar la textura anterior
    texture = LoadAndResizeTexture(texturePath, 32, 32);
}