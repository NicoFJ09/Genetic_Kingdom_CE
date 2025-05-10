#ifndef GAME_PANEL_H
#define GAME_PANEL_H

#include "raylib.h"
#include <array>
#include <vector>
#include <string>

class GamePanel {
private:
    Rectangle bounds; // Área del panel
    std::array<Texture2D, 6> horizontalTextures; // Texturas horizontales
    std::array<Texture2D, 6> verticalTextures;   // Texturas verticales
    Texture2D middleTexture; // Textura para "Middle"
    std::vector<std::vector<int>> map; // Representación del mapa

    // Funciones auxiliares
    Texture2D LoadAndResizeTexture(const std::string& path, int width, int height);
    void DrawMap(); // Lógica para dibujar el mapa

public:
    GamePanel(float x, float y, float width, float height);
    ~GamePanel(); // Liberar las texturas
    void Update(); // Actualizar lógica del panel
    void Draw();   // Dibujar el panel
};

#endif // GAME_PANEL_H