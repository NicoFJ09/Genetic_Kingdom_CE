#ifndef BOTTOM_PANEL_H
#define BOTTOM_PANEL_H

#include "raylib.h"
#include "../map/GrassTile.h"
#include "../map/Map.h"
#include "../core/EconomySystem.h"
#include "TowerBuy.h"
#include "TowerUpgrade.h"
#include <array>

class BottomPanel {
private:
    Rectangle bounds; // Área del panel
    GrassTile* selectedTile; // Puntero al tile seleccionado
    TowerTile* selectedTower; // Puntero a la torre seleccionada
    EconomySystem economySystem; // Sistema de economía
    Texture2D coinTexture; // Textura de la moneda
    TowerBuy towerBuy; // Instancia de TowerBuy
    TowerUpgrade towerUpgrade; // Instancia de TowerUpgrade

public:
    BottomPanel(float x, float y, float width, float height, Map& map);
    ~BottomPanel();
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
    void SetSelectedTower(TowerTile* tower); 
    void SetSelectedTile(GrassTile* tile);
    EconomySystem& GetEconomySystem(); // Obtener el sistema de economía
};

#endif // BOTTOM_PANEL_H