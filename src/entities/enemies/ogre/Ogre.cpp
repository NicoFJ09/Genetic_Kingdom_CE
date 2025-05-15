#include "Ogre.h"

Ogre::Ogre(bool alive, Vector2 position, int frameSpeed, int generation = 1)
    : Enemy(alive, position, frameSpeed,
            alive ? "../assets/textures/enemies/ogre/OgreMoveSpriteSheet.png"
                  : "../assets/textures/enemies/ogre/OgreDeathSpriteSheet.png",
            alive ? 8 : 4,
            "Ogre",      // Tipo de enemigo
            150,         // Salud
            3,           // Velocidad
            15,          // Resistencia a flechas
            10,          // Resistencia a magia
            20,          // Resistencia a artillería
            false,       // No mutado
            generation,  // Generación
            70           // Probabilidad de mutación
    ) {}