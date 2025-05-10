#ifndef GAME_PANEL_H
#define GAME_PANEL_H

#include "raylib.h"
#include <array>

class GamePanel {
private:
    Rectangle bounds; // Área del panel
    std::array<Texture2D, 6> horizontalTextures; // Texturas horizontales
    std::array<Texture2D, 6> verticalTextures;   // Texturas verticales
    Texture2D middleTexture; // Textura para "Middle"

public:
    GamePanel(float x, float y, float width, float height);
    ~GamePanel(); // Liberar las texturas
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
};

#endif // GAME_PANEL_H