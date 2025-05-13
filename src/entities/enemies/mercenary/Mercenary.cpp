#include "Mercenary.h"

Mercenary::Mercenary(bool alive, Vector2 position, int frameSpeed)
    : Enemy(alive, position, frameSpeed,
            alive ? "../assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet.png"
                  : "../assets/textures/enemies/mercenary/MercenaryDeathSpriteSheet.png",
            alive ? 9 : 4,
            "Mercenary", // Tipo de enemigo
            100,         // Salud
            5,           // Velocidad
            8,           // Resistencia a flechas
            3,           // Resistencia a magia
            5,           // Resistencia a artillería
            false,       // No mutado
            70           // Probabilidad de mutación
    ) {}