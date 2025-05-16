#include <cstdlib>   // For rand()
#include <ctime>     // For time()
#include "Ogre.h"

Ogre::Ogre(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation)
    : Enemy(
        alive,
        position,
        frameSpeed,
        mutated ? "../assets/textures/enemies/ogre/OgreMoveSpriteSheet_mutated.png"
                : "../assets/textures/enemies/ogre/OgreMoveSpriteSheet.png",
        8,
        "Ogre",
        getRandomHealth(),    // Salud entre 100 y 150
        getRandomSpeed(),     // Velocidad entre 3.0 y 5.0
        getRandomResist(),  // Resistencia a flechas entre 20 y 40
        0,                   // Resistencia a magia
        0,                   // Resistencia a artillería
        mutated,
        generation,
        10                   // Probabilidad de mutación
    ) {}

// Static or helper functions for randomization
double Ogre::getRandomHealth() {
    return 100.0f + static_cast<float>(rand() % 51); // 100 to 150
}

double Ogre::getRandomSpeed() {
    return 3.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (5.0f - 3.0f))); // 3.0 to 5.0
}

double Ogre::getRandomResist() {
    return 20 + rand() % 21; // 20 to 40
}
