#include "Ogre.h"

Ogre::Ogre(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            mutated ? "../assets/textures/enemies/ogre/OgreMoveSpriteSheet_mutated.png"
                  : "../assets/textures/enemies/ogre/OgreMoveSpriteSheet.png",
            8,
            "Ogre",      // Tipo de enemigo
            150.0,         // Salud
            5.0,           // Velocidad
            40,          // Resistencia a flechas
            0,          // Resistencia a magia
            0,          // Resistencia a artillería
            mutated,       // Mutación
            generation,  // Generación
            70           // Probabilidad de mutación
    ) {}