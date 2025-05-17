#ifndef OGRE_H
#define OGRE_H

#include "../Enemy.h"

class Ogre : public Enemy {
public:
    Ogre(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1, int mutationChance = 5);
    ~Ogre() = default;
    double getRandomHealth();
    double getRandomSpeed();
    double getRandomResist();
};

#endif // OGRE_H