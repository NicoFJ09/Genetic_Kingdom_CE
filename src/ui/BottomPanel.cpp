#include "BottomPanel.h"
#include "../config/Constants.h" // Incluir las constantes de colores

BottomPanel::BottomPanel(float x, float y, float width, float height)
    : bounds({x, y, width, height}), selectedTile(nullptr) {}

void BottomPanel::Update() {
    // Lógica del panel (por ahora vacío)
}

void BottomPanel::Draw() {
    DrawRectangleRec(bounds, PEACH_ORANGE); // Dibujar el área del panel con PEACH_ORANGE

    // Imprimir información del tile seleccionado
    if (selectedTile) {
        Vector2 position = selectedTile->GetPosition();
        DrawText(TextFormat("Selected Tile: (%.0f, %.0f)", position.x, position.y), 
                 bounds.x + 10, bounds.y + 10, 20, BLACK);
    }
}

void BottomPanel::SetSelectedTile(GrassTile* tile) {
    selectedTile = tile; // Actualizar el tile seleccionado
}