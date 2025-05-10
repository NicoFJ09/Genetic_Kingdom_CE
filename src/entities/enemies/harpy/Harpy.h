#ifndef HARPY_H
#define HARPY_H

#include "../Enemy.h"

class Harpy : public Enemy {
public:
    Harpy(bool alive, Vector2 position, int frameSpeed);
    ~Harpy() = default;
};

#endif // HARPY_H