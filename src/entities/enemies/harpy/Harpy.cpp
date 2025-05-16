#include "Harpy.h"

Harpy::Harpy(bool alive, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            alive ? "../assets/textures/enemies/harpy/HarpyMoveSpriteSheet.png"
                  : "../assets/textures/enemies/harpy/HarpyDeathSpriteSheet.png",
            alive ? 23 : 7,
            "Harpy",    // Tipo de enemigo
            60.0,         // Salud
            8.0,         // Velocidad
            0,          // Resistencia a flechas
            0,          // Resistencia a magia
            100,          // Resistencia a artillería
            false,       // No mutado
            generation,  // Generación
            70           // Probabilidad de mutación
    ) {}