#ifndef HARPY_H
#define HARPY_H

#include "../Enemy.h"

class Harpy : public Enemy {
public:
    Harpy(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1, int mutationChance = 5);
    ~Harpy() = default;
    double getRandomHealth();
    double getRandomSpeed();
};

#endif // HARPY_H