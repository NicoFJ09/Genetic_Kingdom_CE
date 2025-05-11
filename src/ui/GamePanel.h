#ifndef GAME_PANEL_H
#define GAME_PANEL_H

#include "raylib.h"
#include "../map/Map.h"

class GamePanel {
private:
    Rectangle bounds; // Área del panel
    Map map;          // Mapa del juego

public:
    GamePanel(float x, float y, float width, float height);
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
    Map& GetMap(); // Obtener el mapa
};

#endif // GAME_PANEL_H