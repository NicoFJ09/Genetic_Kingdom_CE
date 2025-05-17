#ifndef OGRE_H
#define OGRE_H

#include "../Enemy.h"

class Ogre : public Enemy {
public:
    Ogre(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation);
    ~Ogre() = default;
    double getRandomHealth();
    double getRandomSpeed();
    double getRandomResist();
};

#endif // OGRE_H