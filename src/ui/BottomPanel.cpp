#include "BottomPanel.h"
#include "../config/Constants.h" // Incluir las constantes de colores

BottomPanel::BottomPanel(float x, float y, float width, float height)
    : bounds({x, y, width, height}) {}

void BottomPanel::Update() {
    // Lógica del panel (por ahora vacío)
}

void BottomPanel::Draw() {
    DrawRectangleRec(bounds, PEACH_ORANGE); // Dibujar el área del panel con PEACH_ORANGE
}