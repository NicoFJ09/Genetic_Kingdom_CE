#include "SidePanel.h"
#include "../config/Constants.h" // Incluir las constantes de colores

SidePanel::SidePanel(float x, float y, float width, float height)
    : bounds({x, y, width, height}) {}

void SidePanel::Update() {
    // Lógica del panel (por ahora vacío)
}

void SidePanel::Draw() {
    DrawRectangleRec(bounds, RUST_ORANGE); // Dibujar el área del panel con RUST_ORANGE
}