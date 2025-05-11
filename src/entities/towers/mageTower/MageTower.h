#ifndef MAGETOWER_H
#define MAGETOWER_H
#include "../Tower.h"


class MageTower : public Tower {
public:
    MageTower(Vector2 position, int level);
    ~MageTower() = default;
};

#endif 