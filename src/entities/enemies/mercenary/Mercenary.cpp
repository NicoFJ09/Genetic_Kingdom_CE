#include "Mercenary.h"

Mercenary::Mercenary(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            mutated ? "../assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet_mutated.png"
                  : "../assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet.png",
            9,
            "Mercenary", // Tipo de enemigo
            100.0,         // Salud
            7.0,           // Velocidad
            40,           // Resistencia a flechas
            0,           // Resistencia a magia
            40,           // Resistencia a artillería
            false,       // No mutado
            generation,  // Generación
            70           // Probabilidad de mutación
    ) {}