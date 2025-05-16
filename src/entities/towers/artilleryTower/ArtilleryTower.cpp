#include "ArtilleryTower.h"

ArtilleryTower::ArtilleryTower(Vector2 position, int level)
    : Tower(position, level,
        "../assets/textures/towers/towersInMap/ArtilleryLvl1.png", // texture
        60,   // damage
        0.5,    // speed
        3,   // range in pixels
        15    // special attack regeneration time
    )
{
    towerType = "Artillery Tower";
}


void ArtilleryTower::UpdateStats() {
    // Actualizar estadísticas según el nivel
    if (level == 1) {
        damage = 60;
        speed = 0.5;
        range = 3;
        spAttackRegenerationTime = 15;
        texturePath = "../assets/textures/towers/towersInMap/ArtilleryLvl1.png";
    } else if (level == 2) {
        damage = 80;
        speed = 0.7;
        range = 4;
        spAttackRegenerationTime = 13;
        texturePath = "../assets/textures/towers/towersInMap/ArtilleryLvl2.png";
    } else if (level == 3) {
        damage = 105;
        speed = 1.0;
        range = 5;
        spAttackRegenerationTime = 10;
        texturePath = "../assets/textures/towers/towersInMap/ArtilleryLvl3.png";
    }

    // Actualizar la textura usando LoadAndResizeTexture
    UnloadTexture(texture); // Liberar la textura anterior
    texture = LoadAndResizeTexture(texturePath, 32, 32);
}