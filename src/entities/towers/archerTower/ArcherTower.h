#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H
#include "../Tower.h"

class ArcherTower : public Tower {
protected:
    void UpdateStats() override; // Actualizar estadísticas y sprite

public:
    ArcherTower(Vector2 position, int level);
};

#endif