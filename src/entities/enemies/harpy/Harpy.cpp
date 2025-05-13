#include "Harpy.h"

Harpy::Harpy(bool alive, Vector2 position, int frameSpeed)
    : Enemy(alive, position, frameSpeed,
            alive ? "../assets/textures/enemies/harpy/HarpyMoveSpriteSheet.png"
                  : "../assets/textures/enemies/harpy/HarpyDeathSpriteSheet.png",
            alive ? 23 : 7,
            "Harpy",    // Tipo de enemigo
            60,         // Salud
            10,         // Velocidad
            3,          // Resistencia a flechas
            5,          // Resistencia a magia
            2,          // Resistencia a artillería
            false       // No mutado
    ) {}