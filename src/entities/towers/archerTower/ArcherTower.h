#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H
#include "../Tower.h"


class ArcherTower : public Tower {
public:
    ArcherTower(Vector2 position, int level);
    ~ArcherTower() = default;
};

#endif 