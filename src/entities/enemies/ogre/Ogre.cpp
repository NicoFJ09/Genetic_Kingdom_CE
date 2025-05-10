#include "Ogre.h"

Ogre::Ogre(bool alive, Vector2 position, int frameSpeed)
    : Enemy(alive, position, frameSpeed, 
            alive ? "../assets/textures/enemies/ogre/OgreMoveSpriteSheet.png" 
                  : "../assets/textures/enemies/ogre/OgreDeathSpriteSheet.png", 
            alive ? 8 : 4) {}