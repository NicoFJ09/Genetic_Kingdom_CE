#ifndef BOTTOM_PANEL_H
#define BOTTOM_PANEL_H

#include "raylib.h"

class BottomPanel {
private:
    Rectangle bounds; // Área del panel

public:
    BottomPanel(float x, float y, float width, float height);
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
};

#endif // BOTTOM_PANEL_H