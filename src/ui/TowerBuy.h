#ifndef TOWERBUY_H
#define TOWERBUY_H

#include "../map/GrassTile.h"
#include "../map/Map.h"
#include "../core/EconomySystem.h"
#include "../entities/towers/Tower.h"
#include "raylib.h"
#include <array>

class TowerBuy {
private:
    Map& map; // Referencia al mapa
    EconomySystem& economySystem; // Referencia al sistema de economía
    std::array<Rectangle, 3> towerSquares; // Cuadrados para las torres
    int selectedTowerIndex; // Índice de la torre seleccionada (-1 si ninguna está seleccionada)
    Rectangle buyButton; // Botón de compra
    bool buyButtonEnabled; // Estado del botón de compra

    void HandleSelectTower(); // Manejo de los cuadrados de torres
    void HandleBuy(GrassTile*& selectedTile); // Manejo del botón de compra

public:
    TowerBuy(Map& map, EconomySystem& economySystem, float panelX, float panelY, float panelWidth);
    void Update(GrassTile*& selectedTile); // Actualizar lógica de compra
    void Draw(); // Dibujar la UI de compra
};

#endif // TOWERBUY_H