#ifndef GAME_PANEL_H
#define GAME_PANEL_H

#include "raylib.h"
#include "../map/Map.h"

class GamePanel {
private:
    Rectangle bounds; // Panel bounds
    Map map; // Game map

public:
    GamePanel(float x, float y, float width, float height);
    void Update(); // Update logic, including hover detection
    void Draw(); // Draw the game panel
};

#endif // GAME_PANEL_H