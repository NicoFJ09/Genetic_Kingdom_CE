#include "DarkElf.h"

DarkElf::DarkElf(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            mutated ? "../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet_mutated.png"
                  : "../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet.png",
            8,
            "Dark Elf", // Tipo de enemigo
            80.0,         // Salud
            10.0,          // Velocidad
            0,          // Resistencia a flechas
            40,         // Resistencia a magia
            0,          // Resistencia a artillería
            mutated,       // Mutación
            generation,  // Generación
            70           // Probabilidad de mutación
    ) {}