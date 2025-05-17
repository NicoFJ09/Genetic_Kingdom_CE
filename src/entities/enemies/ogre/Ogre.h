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
    Ogre* Clone() const override { return new Ogre(*this); }
};

#endif // OGRE_H