#include "Mercenary.h"

Mercenary::Mercenary(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            mutated ? "../assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet_mutated.png"
                  : "../assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet.png",
            9,
            "Mercenary", // Tipo de enemigo
            getRandomHealth(),         // Salud
            getRandomSpeed(),           // Velocidad
            getRandomResist(),           // Resistencia a flechas
            0,           // Resistencia a magia
            getRandomResist(),           // Resistencia a artillería
            mutated,       // Mutación
            generation,  // Generación
            10           // Probabilidad de mutación
    ) {}

// Static or helper functions for randomization
double Mercenary::getRandomHealth() {
    return 75.0f + static_cast<float>(rand() % 41); // 75 to 125
}

double Mercenary::getRandomSpeed() {
    return 5.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (8.0f - 5.0f))); // 5.0 to 8.0
}

double Mercenary::getRandomResist() {
    return 20 + rand() % 21; // 20 to 40
}
