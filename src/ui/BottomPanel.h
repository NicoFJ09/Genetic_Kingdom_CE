#ifndef BOTTOM_PANEL_H
#define BOTTOM_PANEL_H

#include "raylib.h"
#include "../map/GrassTile.h"
#include "../map/Map.h"
#include "../core/EconomySystem.h"
#include "TowerBuy.h" // Incluir TowerBuy
#include <array>

class BottomPanel {
private:
    Rectangle bounds; // Área del panel
    GrassTile* selectedTile; // Puntero al tile seleccionado
    EconomySystem economySystem; // Sistema de economía
    Texture2D coinTexture; // Textura de la moneda
    TowerBuy towerBuy; // Instancia de TowerBuy

public:
    BottomPanel(float x, float y, float width, float height, Map& map);
    ~BottomPanel();
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
    void SetSelectedTile(GrassTile* tile); // Establecer el tile seleccionado
    EconomySystem& GetEconomySystem(); // Obtener el sistema de economía
};

#endif // BOTTOM_PANEL_H