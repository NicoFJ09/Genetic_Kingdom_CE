#ifndef ARTILLERY_H
#define ARTILLERY_H
#include "../Tower.h"

class ArtilleryTower : public Tower {
protected:
    void UpdateStats() override; // Actualizar estadísticas y sprite

public:
    ArtilleryTower(Vector2 position, int level);
};

#endif