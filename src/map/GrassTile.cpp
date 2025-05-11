#include "GrassTile.h"
#include "raylib.h"
#include "../config/Constants.h"

GrassTile::GrassTile(Vector2 position, Color color)
    : Tile(position), color(color), isHovered(false), isSelected(false) {}

void GrassTile::Draw() const {
    // Dibuja el tile con el color basado en el estado
    Color drawColor = isSelected ? DARKGREEN : (isHovered ? OLIVE_DRAB : color);
    DrawRectangle(position.x, position.y, 32, 32, drawColor);
}

void GrassTile::CheckHover() {
    // Define el rectángulo para el tile
    Rectangle tileRect = { position.x, position.y, 32, 32 };

    // Actualiza el estado de hover
    isHovered = CheckCollisionPointRec(GetMousePosition(), tileRect);
}

void GrassTile::SetSelected(bool selected) {
    isSelected = selected;
}

bool GrassTile::IsSelected() const {
    return isSelected;
}