#ifndef ARTILLERY_H
#define ARTILLERY_H
#include "../Tower.h"


class ArtilleryTower : public Tower {
public:
    ArtilleryTower(Vector2 position, int level);
    ~ArtilleryTower() = default;
};

#endif 