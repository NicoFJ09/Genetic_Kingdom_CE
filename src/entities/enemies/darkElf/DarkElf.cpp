#include "DarkElf.h"

DarkElf::DarkElf(bool alive, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            alive ? "../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet.png"
                  : "../assets/textures/enemies/darkelf/DarkElfDeathSpriteSheet.png",
            alive ? 8 : 7,
            "Dark Elf", // Tipo de enemigo
            80.0,         // Salud
            6.0,          // Velocidad
            5,          // Resistencia a flechas
            10,         // Resistencia a magia
            8,          // Resistencia a artillería
            false,       // No mutado
            generation,  // Generación
            70           // Probabilidad de mutación
    ) {}