#include "Harpy.h"

Harpy::Harpy(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation, int mutationChance )
    : Enemy(alive, position, frameSpeed,
            mutated ? "../assets/textures/enemies/harpy/HarpyMoveSpriteSheet_mutated.png"
                  : "../assets/textures/enemies/harpy/HarpyMoveSpriteSheet.png",
            23,
            "Harpy",    // Tipo de enemigo
            getRandomHealth(),         // Salud
            getRandomSpeed(),         // Velocidad
            0,          // Resistencia a flechas
            0,          // Resistencia a magia
            100,          // Resistencia a artillería
            mutated,       // Mutación
            generation,  // Generación
            mutationChance           // Probabilidad de mutación
    ) {}

// Static or helper functions for randomization
double Harpy::getRandomHealth() {
    return 40.0f + static_cast<float>(rand() % 31); // 40 to 70
}

double Harpy::getRandomSpeed() {
    return 6.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (9.0f - 6.0f))); // 6.0 to 9.0
}
