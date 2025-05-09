#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include "raylib.h"

class SidePanel {
private:
    Rectangle bounds; // Área del panel

public:
    SidePanel(float x, float y, float width, float height);
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
};

#endif // SIDE_PANEL_H