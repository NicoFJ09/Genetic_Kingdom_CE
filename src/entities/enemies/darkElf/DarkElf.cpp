#include "DarkElf.h"

DarkElf::DarkElf(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation, int mutationChance)
    : Enemy(alive, position, frameSpeed,
            mutated ? "../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet_mutated.png"
                  : "../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet.png",
            8,
            "Dark Elf", // Tipo de enemigo
            getRandomHealth(),         // Salud
            getRandomSpeed(),          // Velocidad
            0,          // Resistencia a flechas
            getRandomResist() ,         // Resistencia a magia
            0,          // Resistencia a artillería
            mutated,       // Mutación
            generation,  // Generación
            mutationChance           // Probabilidad de mutación
    ) {}

// Static or helper functions for randomization
double DarkElf::getRandomHealth() {
    return 70.0f + static_cast<float>(rand() % 31); // 70 to 100
}

double DarkElf::getRandomSpeed() {
    return 8.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (11.0f - 8.0f))); // 8.0 to 11.0
}

double DarkElf::getRandomResist() {
    return 20 + rand() % 21; // 20 to 40
}
