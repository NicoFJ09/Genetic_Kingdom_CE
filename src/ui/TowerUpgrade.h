#ifndef TOWERUPGRADE_H
#define TOWERUPGRADE_H

#include "../map/TowerTile.h"
#include "raylib.h"
#include <string>

class TowerUpgrade {
private:
    bool isVisible;           // Estado de visibilidad
    Rectangle bounds;         // Dimensiones del panel inferior

public:
    TowerUpgrade(float panelX, float panelY, float panelWidth, float panelHeight);
    void Update(TowerTile*& selectedTower); // Actualizar la lógica de mejora
    void Draw(TowerTile* selectedTower);   // Dibujar la pantalla de mejora
};

#endif // TOWERUPGRADE_H