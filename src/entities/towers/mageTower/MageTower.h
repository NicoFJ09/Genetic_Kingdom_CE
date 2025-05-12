#ifndef MAGETOWER_H
#define MAGETOWER_H
#include "../Tower.h"

class MageTower : public Tower {
protected:
    void UpdateStats() override; // Actualizar estadísticas y sprite

public:
    MageTower(Vector2 position, int level);
};

#endif