#ifndef BOTTOM_PANEL_H
#define BOTTOM_PANEL_H

#include "raylib.h"
#include "../map/GrassTile.h" // Incluir GrassTile para manejar el tile seleccionado

class BottomPanel {
private:
    Rectangle bounds; // Área del panel
    GrassTile* selectedTile; // Puntero al tile seleccionado

public:
    BottomPanel(float x, float y, float width, float height);
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
    void SetSelectedTile(GrassTile* tile); // Establecer el tile seleccionado
};

#endif // BOTTOM_PANEL_H