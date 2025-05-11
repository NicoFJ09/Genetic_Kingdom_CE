#include "Map.h"
#include "../config/Constants.h"
#include "Tile.h"
#include "PathTile.h"
#include "GrassTile.h"

Map::Map() {
    // Load and resize textures
    horizontalTextures[0] = LoadAndResizeTexture("../assets/map/tiles/Middle.png", 32, 32);
    horizontalTextures[1] = LoadAndResizeTexture("../assets/map/tiles/Horizontal/H_1.png", 32, 32);
    horizontalTextures[2] = LoadAndResizeTexture("../assets/map/tiles/Horizontal/H_2.png", 32, 32);
    horizontalTextures[3] = horizontalTextures[0]; // Reuse "Middle"
    horizontalTextures[4] = LoadAndResizeTexture("../assets/map/tiles/Horizontal/H_3.png", 32, 32);
    horizontalTextures[5] = LoadAndResizeTexture("../assets/map/tiles/Horizontal/H_4.png", 32, 32);

    verticalTextures[0] = LoadAndResizeTexture("../assets/map/tiles/Middle.png", 32, 32);
    verticalTextures[1] = LoadAndResizeTexture("../assets/map/tiles/Vertical/V_1.png", 32, 32);
    verticalTextures[2] = LoadAndResizeTexture("../assets/map/tiles/Vertical/V_2.png", 32, 32);
    verticalTextures[3] = verticalTextures[0]; // Reuse "Middle"
    verticalTextures[4] = LoadAndResizeTexture("../assets/map/tiles/Vertical/V_3.png", 32, 32);
    verticalTextures[5] = LoadAndResizeTexture("../assets/map/tiles/Vertical/V_4.png", 32, 32);

    middleTexture = LoadAndResizeTexture("../assets/map/tiles/Middle.png", 32, 32);
}

Map::~Map() {
    // Unload textures
    for (auto& texture : horizontalTextures) {
        UnloadTexture(texture);
    }
    for (auto& texture : verticalTextures) {
        UnloadTexture(texture);
    }
    UnloadTexture(middleTexture);
}

Texture2D Map::LoadAndResizeTexture(const std::string& path, int width, int height) {
    Image img = LoadImage(path.c_str());
    if (img.data == nullptr) {
        TraceLog(LOG_ERROR, "Failed to load image: %s", path.c_str());
        return {0}; // Return an invalid texture
    }
    ImageResize(&img, width, height);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

void Map::LoadFromArray(const std::array<std::array<int, 31>, 19>& mapData) {
    tiles.clear(); // Limpia los tiles existentes
    std::vector<bool> isVerticalPath(mapData[0].size(), false); // Rastrea caminos verticales
    std::vector<size_t> verticalIndices(mapData[0].size(), 0);  // Índices de sprites verticales

    // Paso 1: Identificar caminos verticales
    for (size_t col = 0; col < mapData[0].size(); ++col) {
        bool inVerticalSequence = false;

        for (size_t row = 0; row < mapData.size(); ++row) {
            if (mapData[row][col] == 0) { // Camino
                bool isVertical = false;

                // Verifica continuidad vertical
                if (row > 0 && row < mapData.size() - 1) {
                    if (mapData[row - 1][col] == 0 || mapData[row + 1][col] == 0) {
                        isVertical = true;
                    }
                } else if (row == 0 && row < mapData.size() - 1) {
                    if (mapData[row + 1][col] == 0) {
                        isVertical = true;
                    }
                } else if (row > 0 && row == mapData.size() - 1) {
                    if (mapData[row - 1][col] == 0) {
                        isVertical = true;
                    }
                }

                if (isVertical) {
                    if (!inVerticalSequence) {
                        inVerticalSequence = true;
                        verticalIndices[col] = 0; // Reinicia el índice
                    }
                    isVerticalPath[col] = true;
                }
            } else {
                inVerticalSequence = false; // Rompe la secuencia vertical
            }
        }
    }

    // Paso 2: Colocar tiles
    for (size_t row = 0; row < mapData.size(); ++row) {
        std::vector<std::unique_ptr<Tile>> tileRow;
        size_t horizontalIndex = 0; // Índice de sprites horizontales
        bool inHorizontalSequence = false;

        for (size_t col = 0; col < mapData[row].size(); ++col) {
            Vector2 position = { static_cast<float>(col * 32), static_cast<float>(row * 32) };
            int tileType = mapData[row][col];

            if (tileType == 0) { // Camino
                bool isHorizontal = true;

                // Verifica si es parte de un camino vertical
                if (isVerticalPath[col]) {
                    if ((row > 0 && mapData[row - 1][col] == 0) ||
                        (row < mapData.size() - 1 && mapData[row + 1][col] == 0)) {
                        isHorizontal = false;
                    }
                }

                if (isHorizontal) {
                    if (col == 0 || mapData[row][col - 1] != 0) {
                        horizontalIndex = 0; // Reinicia el índice horizontal
                        inHorizontalSequence = true;
                    }

                    // Agrega un tile de camino horizontal
                    tileRow.emplace_back(std::make_unique<PathTile>(position, horizontalTextures[horizontalIndex % 6]));
                    horizontalIndex++;
                } else {
                    if (row == 0 || mapData[row - 1][col] != 0) {
                        verticalIndices[col] = 0; // Reinicia el índice vertical
                    }

                    // Agrega un tile de camino vertical
                    tileRow.emplace_back(std::make_unique<PathTile>(position, verticalTextures[verticalIndices[col] % 6]));
                    verticalIndices[col]++;
                }
            } else { // Césped
                // Agrega un tile de césped con color OLIVE_GREEN
                tileRow.emplace_back(std::make_unique<GrassTile>(position, OLIVE_GREEN));
                inHorizontalSequence = false;
            }
        }
        tiles.emplace_back(std::move(tileRow)); // Mueve la fila al vector principal
    }
}

void Map::CheckHover() const {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            // Verifica si el tile es un GrassTile
            auto grassTile = dynamic_cast<GrassTile*>(tile.get());
            if (grassTile) {
                grassTile->CheckHover(); // Llama a CheckHover solo para GrassTile
            }
        }
    }
}

void Map::Draw() const {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            tile->Draw(); // Usa -> para acceder al método del objeto apuntado
        }
    }
}