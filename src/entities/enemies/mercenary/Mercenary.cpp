#include "Mercenary.h"

Mercenary::Mercenary(bool alive, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            alive ? "../assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet.png"
                  : "../assets/textures/enemies/mercenary/MercenaryDeathSpriteSheet.png",
            alive ? 9 : 4,
            "Mercenary", // Tipo de enemigo
            100.0,         // Salud
            7.0,           // Velocidad
            30,           // Resistencia a flechas
            0,           // Resistencia a magia
            30,           // Resistencia a artillería
            false,       // No mutado
            generation,  // Generación
            70           // Probabilidad de mutación
    ) {}