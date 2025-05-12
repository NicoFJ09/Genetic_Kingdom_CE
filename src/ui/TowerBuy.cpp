#include "TowerBuy.h"
#include "../config/Constants.h"

TowerBuy::TowerBuy(Map& map, EconomySystem& economySystem, float panelX, float panelY, float panelWidth, float panelHeight)
    : map(map), economySystem(economySystem), selectedTowerIndex(-1), buyButtonEnabled(false), isVisible(false) {
    // Ajustar las dimensiones de los cuadrados de torres
    float squareWidth = 100;
    float squareHeight = 116;
    float labelHeight = 20; // Altura del texto de las etiquetas

    // Limitar el ancho total a dos tercios del ancho del panel
    float usableWidth = panelWidth * (2.0f / 3.0f);

    // Calcular el espaciado para que los cuadrados estén equidistantes dentro del área usable
    size_t numSquares = towerSquares.size();
    float totalSquaresWidth = numSquares * squareWidth;
    float totalSpacingWidth = usableWidth - totalSquaresWidth;
    float spacing = totalSpacingWidth / (numSquares + 1); // Espaciado entre cuadrados

    // Posición inicial en Y para los cuadrados (centrados verticalmente en el panel)
    float totalHeight = squareHeight + labelHeight + 10; // Altura de los cuadrados + etiquetas + padding
    float initialY = panelY + (panelHeight - totalHeight) / 2;

    // Inicializar los cuadrados de torres dentro del área usable
    for (size_t i = 0; i < numSquares; ++i) {
        float squareX = panelX + spacing + i * (squareWidth + spacing);
        towerSquares[i] = {squareX, initialY, squareWidth, squareHeight};
    }

    // Cargar texturas redimensionadas para las torres de nivel 1
    towerTextures[0] = LoadAndResizeTexture(ARCHER_TOWER_LVL1, squareWidth-10, squareHeight-10);
    towerTextures[1] = LoadAndResizeTexture(ARTILLERY_TOWER_LVL1, squareWidth-10, squareHeight-10);
    towerTextures[2] = LoadAndResizeTexture(MAGE_TOWER_LVL1, squareWidth-10, squareHeight-10);

    // Mantener el botón de compra en su posición actual
    buyButton = {panelX + panelWidth - 120, panelY + 80, 100, 40};
}

TowerBuy::~TowerBuy() {
    // Liberar las texturas cargadas
    for (auto& texture : towerTextures) {
        UnloadTexture(texture);
    }
}

Texture2D TowerBuy::LoadAndResizeTexture(const std::string& path, int width, int height) {
    Image img = LoadImage(path.c_str());
    if (img.data == nullptr) {
        TraceLog(LOG_ERROR, "Failed to load image: %s", path.c_str());
        return {0}; // Retornar una textura inválida
    }
    ImageResize(&img, width, height);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

void TowerBuy::Update(GrassTile*& selectedTile) {
    // Mostrar u ocultar la UI según si hay un tile seleccionado
    isVisible = (selectedTile != nullptr);

    if (isVisible) {
        HandleSelectTower(); // Manejar la selección de la torre
        HandleBuy(selectedTile); // Manejar la lógica de compra
    } else {
        buyButtonEnabled = false; // Deshabilitar el botón si la UI no está visible
    }
}
void TowerBuy::Draw() {
    if (!isVisible) return; // No dibujar si la UI no está visible

    // Dibujar los bordes de los cuadrados de torres y sus etiquetas
    for (size_t i = 0; i < towerSquares.size(); ++i) {
        // Dibujar el contorno del cuadrado
        Color outlineColor = (selectedTowerIndex == (int)i) ? WHITE : BLACK;
        DrawRectangleLinesEx(towerSquares[i], 2, outlineColor);

        // Calcular las coordenadas para centrar la textura dentro del cuadrado
        float textureWidth = towerSquares[i].width;  // La textura tiene el mismo ancho que el cuadrado
        float textureHeight = towerSquares[i].height; // La textura tiene la misma altura que el cuadrado
        float textureX = towerSquares[i].x + (towerSquares[i].width - textureWidth) / 2 + 7.5;
        float textureY = towerSquares[i].y + (towerSquares[i].height - textureHeight) / 2 + 10;

        // Dibujar la textura de la torre centrada dentro del cuadrado
        DrawTexture(towerTextures[i], textureX, textureY, WHITE);

        // Dibujar la etiqueta debajo del cuadrado
        const char* labelText = Towers[i].name.c_str();
        int fontSize = 12;
        int textWidth = MeasureText(labelText, fontSize);
        float textX = towerSquares[i].x + (towerSquares[i].width - textWidth) / 2;
        float textY = towerSquares[i].y + towerSquares[i].height + 5; // Debajo del cuadrado
        DrawText(labelText, textX, textY, fontSize, WHITE);
    }

    // Dibujar el botón de compra
    Color buyColor = buyButtonEnabled ? RUST_ORANGE : GRAY; // Usar RUST_ORANGE para el botón habilitado
    DrawRectangleRec(buyButton, buyColor);
    DrawRectangleLinesEx(buyButton, 2, BLACK);

    // Centrar el texto "Buy" en el botón
    const char* buttonText = "Buy";
    int fontSize = 20;
    int textWidth = MeasureText(buttonText, fontSize);
    int textHeight = fontSize; // Aproximación: la altura del texto es igual al tamaño de la fuente
    float textX = buyButton.x + (buyButton.width - textWidth) / 2;
    float textY = buyButton.y + (buyButton.height - textHeight) / 2;

    DrawText(buttonText, textX, textY, fontSize, WHITE);
}

void TowerBuy::HandleSelectTower() {
    for (size_t i = 0; i < towerSquares.size(); ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), towerSquares[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedTowerIndex = i; // Seleccionar la torre
            TraceLog(LOG_INFO, "Tower selected: %s", Towers[i].name.c_str());
        }
    }
}

void TowerBuy::HandleBuy(GrassTile*& selectedTile) {
    if (selectedTowerIndex != -1) {
        const TowerInfo& tower = Towers[selectedTowerIndex];
        int cost = tower.costLevel1; // Usar el costo del nivel 1 como ejemplo

        // Habilitar o deshabilitar el botón de compra según el balance y la selección de torre
        buyButtonEnabled = (economySystem.GetBalance() >= cost);

        if (buyButtonEnabled && CheckCollisionPointRec(GetMousePosition(), buyButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            economySystem.DecreaseFromBalance(cost); // Reducir el balance
            TraceLog(LOG_INFO, "Bought: %s", tower.name.c_str()); // Imprimir mensaje

            // Reemplazar el tile seleccionado con un TowerTile que tenga la torre específica
            TowerTile* newTile = map.ReplaceTileWithTower(selectedTile, tower.name, 1); // Nivel inicial 1

            // Reiniciar la selección y deshabilitar los botones
            selectedTile = nullptr;
            selectedTowerIndex = -1;
            buyButtonEnabled = false;
        }
    } else {
        buyButtonEnabled = false; // Deshabilitar el botón si no hay torre seleccionada
    }
}
