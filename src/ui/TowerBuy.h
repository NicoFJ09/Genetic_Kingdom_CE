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
    std::array<Texture2D, 3> towerTextures; // Texturas redimensionadas de las torres
    int selectedTowerIndex; // Índice de la torre seleccionada (-1 si ninguna está seleccionada)
    Rectangle buyButton; // Botón de compra
    bool buyButtonEnabled; // Estado del botón de compra
    bool isVisible;

    void HandleSelectTower(); // Manejo de los cuadrados de torres
    void HandleBuy(GrassTile*& selectedTile); // Manejo del botón de compra

    // Nueva función para cargar y redimensionar texturas
    Texture2D LoadAndResizeTexture(const std::string& path, int width, int height);

public:
    TowerBuy(Map& map, EconomySystem& economySystem, float panelX, float panelY, float panelWidth, float panelHeight);
    ~TowerBuy(); // Liberar texturas
    void Update(GrassTile*& selectedTile); // Actualizar lógica de compra
    void Draw(); // Dibujar la UI de compra
};

#endif // TOWERBUY_H