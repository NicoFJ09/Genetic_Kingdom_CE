#ifndef MERCENARY_H
#define MERCENARY_H

#include "../Enemy.h"

class Mercenary : public Enemy {
public:
    Mercenary(bool alive, Vector2 position, int frameSpeed);
    ~Mercenary() = default;
};

#endif // MERCENARY_H