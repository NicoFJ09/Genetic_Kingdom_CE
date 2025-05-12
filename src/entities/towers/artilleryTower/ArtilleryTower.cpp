#include "ArtilleryTower.h"

ArtilleryTower::ArtilleryTower(Vector2 position, int level)
    : Tower(position, level,
        level == 1 ? "../assets/textures/towers/towersInMap/ArtilleryLvl1.png" :
        level == 2 ? "../assets/textures/towers/towersInMap/ArtilleryLvl2.png" :
                     "../assets/textures/towers/towersInMap/ArtilleryLvl3.png",
        level == 1 ? 20 : level == 2 ? 30 : 40,           // damage
        level == 1 ? 1  : level == 2 ? 2  : 3,            // speed
        level == 1 ? 50 : level == 2 ? 100 : 150,        // range in pixels
        level == 1 ? 15 : level == 2 ? 10 : 5,           // attack regen
        level == 1 ? 70 : level == 2 ? 50 : 35          // special attack regen
    ){
    towerType = "Artillery Tower";
}

void ArtilleryTower::UpdateStats() {
    // Actualizar estadísticas según el nivel
    if (level == 1) {
        damage = 20;
        speed = 1;
        range = 50;
        attackRegenerationTime = 15;
        spAttackRegenerationTime = 70;
        texturePath = "../assets/textures/towers/towersInMap/ArtilleryLvl1.png";
    } else if (level == 2) {
        damage = 30;
        speed = 2;
        range = 100;
        attackRegenerationTime = 10;
        spAttackRegenerationTime = 50;
        texturePath = "../assets/textures/towers/towersInMap/ArtilleryLvl2.png";
    } else if (level == 3) {
        damage = 40;
        speed = 3;
        range = 150;
        attackRegenerationTime = 5;
        spAttackRegenerationTime = 35;
        texturePath = "../assets/textures/towers/towersInMap/ArtilleryLvl3.png";
    }

    // Actualizar la textura usando LoadAndResizeTexture
    UnloadTexture(texture); // Liberar la textura anterior
    texture = LoadAndResizeTexture(texturePath, 32, 32);
}