#include "GamePanel.h"
#include "../config/Constants.h"
#include <vector>

// Ruta base para los archivos de tiles

GamePanel::GamePanel(float x, float y, float width, float height)
    : bounds({x, y, width, height}) {
    // Cargar y redimensionar texturas horizontales
    Image img = LoadImage((MAP_PATH + "Horizontal/H_1.png").c_str());
    ImageResize(&img, 32, 32);
    horizontalTextures[1] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage((MAP_PATH + "Horizontal/H_2.png").c_str());
    ImageResize(&img, 32, 32);
    horizontalTextures[2] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage((MAP_PATH + "Horizontal/H_3.png").c_str());
    ImageResize(&img, 32, 32);
    horizontalTextures[4] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage((MAP_PATH + "Horizontal/H_4.png").c_str());
    ImageResize(&img, 32, 32);
    horizontalTextures[5] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage((MAP_PATH + "Middle.png").c_str());
    ImageResize(&img, 32, 32);
    horizontalTextures[0] = LoadTextureFromImage(img);
    horizontalTextures[3] = horizontalTextures[0]; // Reutilizar la textura "Middle"
    UnloadImage(img);

    // Cargar y redimensionar texturas verticales
    img = LoadImage((MAP_PATH + "Vertical/V_1.png").c_str());
    ImageResize(&img, 32, 32);
    verticalTextures[1] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage((MAP_PATH + "Vertical/V_2.png").c_str());
    ImageResize(&img, 32, 32);
    verticalTextures[2] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage((MAP_PATH + "Vertical/V_3.png").c_str());
    ImageResize(&img, 32, 32);
    verticalTextures[4] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage((MAP_PATH + "Vertical/V_4.png").c_str());
    ImageResize(&img, 32, 32);
    verticalTextures[5] = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage((MAP_PATH + "Middle.png").c_str());
    ImageResize(&img, 32, 32);
    verticalTextures[0] = LoadTextureFromImage(img);
    verticalTextures[3] = verticalTextures[0]; // Reutilizar la textura "Middle"
    UnloadImage(img);

    // Cargar y redimensionar textura para "Middle"
    img = LoadImage((MAP_PATH + "Middle.png").c_str());
    ImageResize(&img, 32, 32);
    middleTexture = LoadTextureFromImage(img);
    UnloadImage(img);
}

GamePanel::~GamePanel() {
    // Liberar texturas horizontales
    for (auto& texture : horizontalTextures) {
        UnloadTexture(texture);
    }

    // Liberar texturas verticales
    for (auto& texture : verticalTextures) {
        UnloadTexture(texture);
    }

    // Liberar textura "Middle"
    UnloadTexture(middleTexture);
}

void GamePanel::Update() {
    // Lógica del panel (por ahora vacío)
}

void GamePanel::Draw() {
    // Dibujar el fondo del panel con OLIVE_GREEN
    DrawRectangleRec(bounds, OLIVE_GREEN);

    // Inicializar vectores para seguimiento de caminos verticales
    std::vector<bool> isVerticalPath(map[0].size(), false); // Para identificar caminos verticales
    std::vector<size_t> verticalIndices(map[0].size(), 0);  // Índices para sprites verticales

    // Primer paso: identificar caminos verticales
    for (size_t col = 0; col < map[0].size(); ++col) {
        bool inVerticalSequence = false;

        for (size_t row = 0; row < map.size(); ++row) {
            if (map[row][col] == 0) { // Es un camino
                bool isVertical = false;

                // Verificar si hay continuidad vertical
                if (row > 0 && row < map.size() - 1) {
                    if (map[row - 1][col] == 0 || map[row + 1][col] == 0) {
                        isVertical = true;
                    }
                } else if (row == 0 && row < map.size() - 1) {
                    if (map[row + 1][col] == 0) {
                        isVertical = true;
                    }
                } else if (row > 0 && row == map.size() - 1) {
                    if (map[row - 1][col] == 0) {
                        isVertical = true;
                    }
                }

                if (isVertical) {
                    if (!inVerticalSequence) {
                        inVerticalSequence = true;
                        verticalIndices[col] = 0; // Reiniciar índice
                    }
                    isVerticalPath[col] = true;
                }
            } else {
                inVerticalSequence = false; // Interrumpir secuencia vertical
            }
        }
    }

    // Reiniciar los índices para el dibujo real
    for (size_t col = 0; col < verticalIndices.size(); ++col) {
        verticalIndices[col] = 0;
    }

    // Segundo paso: dibujar el mapa
    for (size_t row = 0; row < map.size(); ++row) {
        size_t horizontalIndex = 0; // Índice para sprites horizontales
        bool inHorizontalSequence = false;

        for (size_t col = 0; col < map[row].size(); ++col) {
            // Calcular la posición del rectángulo
            float x = bounds.x + col * 32; // Cada celda tiene un ancho de 32
            float y = bounds.y + row * 32; // Cada celda tiene una altura de 32

            int tileType = map[row][col];

            if (tileType == 0) { // Es un camino
                bool isHorizontal = true;

                // Verificar si es parte de un camino vertical
                if (isVerticalPath[col]) {
                    if ((row > 0 && map[row - 1][col] == 0) ||
                        (row < map.size() - 1 && map[row + 1][col] == 0)) {
                        isHorizontal = false;
                    }
                }

                if (isHorizontal) {
                    if (col == 0 || map[row][col - 1] != 0) {
                        horizontalIndex = 0; // Reiniciar índice horizontal
                        inHorizontalSequence = true;
                    }

                    // Dibujar sprite horizontal
                    DrawTexture(horizontalTextures[horizontalIndex % 6], x, y, WHITE);
                    horizontalIndex++;
                } else {
                    if (row == 0 || map[row - 1][col] != 0) {
                        verticalIndices[col] = 0; // Reiniciar índice vertical
                    }

                    // Dibujar sprite vertical
                    DrawTexture(verticalTextures[verticalIndices[col] % 6], x, y, WHITE);
                    verticalIndices[col]++;
                }
            } else if (tileType == 3) {
                // Dibujar un rectángulo OLIVE_DRAB para los valores 3
                DrawRectangle(x, y, 32, 32, OLIVE_DRAB);
                inHorizontalSequence = false;
            }
            // Si no es 0 ni 3, no dibujar nada
        }
    }
}