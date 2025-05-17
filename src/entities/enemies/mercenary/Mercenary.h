#ifndef MERCENARY_H
#define MERCENARY_H

#include "../Enemy.h"

class Mercenary : public Enemy {
public:
    Mercenary(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1, int mutationChance = 5);
    ~Mercenary() = default;
    double getRandomHealth();
    double getRandomSpeed();
    double getRandomResist();
};

#endif // MERCENARY_H