#ifndef OGRE_H
#define OGRE_H

#include "../Enemy.h"

class Ogre : public Enemy {
public:
    Ogre(bool alive, Vector2 position, int frameSpeed);
    ~Ogre() = default;
};

#endif // OGRE_H