#ifndef BOTTOM_PANEL_H
#define BOTTOM_PANEL_H

#include "raylib.h"
#include "../map/GrassTile.h"
#include "../map/Map.h" // Incluir Map
#include "../core/EconomySystem.h"
#include "../config/Constants.h"
#include <array>

class BottomPanel {
private:
    Rectangle bounds; // Área del panel
    GrassTile* selectedTile; // Puntero al tile seleccionado
    EconomySystem economySystem; // Sistema de economía
    Texture2D coinTexture; // Textura de la moneda
    std::array<Rectangle, 3> towerSquares; // Cuadrados para las torres
    int selectedTowerIndex; // Índice de la torre seleccionada (-1 si ninguna está seleccionada)
    Rectangle buyButton; // Botón de compra
    bool buyButtonEnabled; // Estado del botón de compra
    Map& map; // Referencia al mapa

    void DrawUI(); // Lógica de la UI
    void HandleSelectTower(); // Manejo de los cuadrados de torres
    void HandleBuy(); // Manejo del botón de compra

public:
    BottomPanel(float x, float y, float width, float height, Map& map); // Constructor actualizado
    ~BottomPanel();
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
    void SetSelectedTile(GrassTile* tile); // Establecer el tile seleccionado
    EconomySystem& GetEconomySystem(); // Obtener el sistema de economía
};

#endif // BOTTOM_PANEL_H