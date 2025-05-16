#include "DarkElf.h"

DarkElf::DarkElf(bool alive, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            alive ? "../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet.png"
                  : "../assets/textures/enemies/darkelf/DarkElfDeathSpriteSheet.png",
            alive ? 8 : 7,
            "Dark Elf", // Tipo de enemigo
            80.0,         // Salud
            10.0,          // Velocidad
            0,          // Resistencia a flechas
            30,         // Resistencia a magia
            0,          // Resistencia a artillería
            false,       // No mutado
            generation,  // Generación
            70           // Probabilidad de mutación
    ) {}