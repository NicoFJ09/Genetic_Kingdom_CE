#ifndef HARPY_H
#define HARPY_H

#include "../Enemy.h"

class Harpy : public Enemy {
public:
    Harpy(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation);
    ~Harpy() = default;
    double getRandomHealth();
    double getRandomSpeed();
    Harpy* Clone() const override { return new Harpy(*this); }
};

#endif // HARPY_H