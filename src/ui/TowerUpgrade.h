#ifndef TOWERUPGRADE_H
#define TOWERUPGRADE_H

#include "../core/EconomySystem.h"
#include "../map/TowerTile.h"
#include "raylib.h"
#include <string>

class TowerUpgrade {
private:
    bool isVisible;           // Estado de visibilidad
    bool isButtonPressed;     // Estado del botón de mejora
    Rectangle bounds;         // Dimensiones del panel inferior
    EconomySystem& economySystem; 

    void HandleUpgrade(TowerTile*& selectedTower); // Manejar la lógica de mejora

public:
    TowerUpgrade(float panelX, float panelY, float panelWidth, float panelHeight, EconomySystem& economySystem);
    void Update(TowerTile*& selectedTower); // Actualizar la lógica de mejora
    void Draw(TowerTile* selectedTower);   // Dibujar la pantalla de mejora
};

#endif // TOWERUPGRADE_H