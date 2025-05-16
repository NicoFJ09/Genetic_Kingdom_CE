#include "Harpy.h"

Harpy::Harpy(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            mutated ? "../assets/textures/enemies/harpy/HarpyMoveSpriteSheet_mutated.png"
                  : "../assets/textures/enemies/harpy/HarpyMoveSpriteSheet.png",
            23,
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