#include "BottomPanel.h"
#include "../config/Constants.h"

BottomPanel::BottomPanel(float x, float y, float width, float height, Map& map)
    : bounds({x, y, width, height}),
      selectedTile(nullptr),
      economySystem(),
      selectedTowerIndex(-1),
      buyButton({x + width - 120, y + 80, 100, 40}),
      buyButtonEnabled(false),
      map(map) { // Inicializar la referencia al mapa
    // Cargar la textura de la moneda
    coinTexture = LoadTexture("../assets/ui/coin/figueres_coin.png");

    // Inicializar los cuadrados de torres
    float squareSize = 50;
    float spacing = 20;
    for (size_t i = 0; i < towerSquares.size(); ++i) {
        towerSquares[i] = {x + 10 + i * (squareSize + spacing), y + 50, squareSize, squareSize};
    }
}

BottomPanel::~BottomPanel() {
    // Descargar la textura de la moneda
    UnloadTexture(coinTexture);
}

void BottomPanel::Update() {
    // Manejar los cuadrados de torres y el botón de compra si hay un tile seleccionado
    if (selectedTile) {
        HandleSelectTower();
        HandleBuy();
    }
}

void BottomPanel::Draw() {
    DrawRectangleRec(bounds, PEACH_ORANGE); // Dibujar el fondo del panel

    // Configuración del texto y la moneda
    const char* balanceText = TextFormat("Balance: %d", economySystem.GetBalance());
    int fontSize = 20;
    int textWidth = MeasureText(balanceText, fontSize);
    int textHeight = fontSize; // Aproximación
    int coinSize = 47;         // Tamaño de la moneda
    int spacing = 10;          // Espaciado entre elementos

    // Posición de la moneda (alineada a la derecha dentro del panel)
    int coinX = bounds.x + bounds.width - spacing - coinSize;
    int coinY = bounds.y + spacing; // Espaciado desde la parte superior del panel

    // Posición del texto (a la izquierda de la moneda)
    int balanceX = coinX - spacing - textWidth;
    int balanceY = bounds.y + spacing + (coinSize - textHeight) / 2; // Centrado relativo a la moneda

    // Dibujar los elementos
    DrawText(balanceText, balanceX, balanceY, fontSize, BLACK);
    DrawTexture(coinTexture, coinX, coinY, WHITE);

    // Dibujar la UI solo si hay un tile seleccionado
    if (selectedTile) {
        DrawUI();
    }
}
void BottomPanel::DrawUI() {
    // Colores únicos para cada cuadrado de torre
    const std::array<Color, 3> towerColors = {RED, GREEN, BLUE};

    // Dibujar los cuadrados de torres
    for (size_t i = 0; i < towerSquares.size(); ++i) {
        Color fillColor = towerColors[i];
        DrawRectangleRec(towerSquares[i], fillColor);

        // Contorno blanco si está seleccionado, negro si no
        Color outlineColor = (selectedTowerIndex == (int)i) ? WHITE : BLACK;
        DrawRectangleLinesEx(towerSquares[i], 2, outlineColor);
    }

    // Dibujar el botón de compra
    Color buyColor = buyButtonEnabled ? RUST_ORANGE : GRAY;
    DrawRectangleRec(buyButton, buyColor);
    DrawRectangleLinesEx(buyButton, 2, BLACK);
    DrawText("Buy", buyButton.x + 25, buyButton.y + 10, 20, WHITE);
}

void BottomPanel::SetSelectedTile(GrassTile* tile) {
    // Si hay un tile previamente seleccionado, deseleccionarlo
    if (selectedTile) {
        selectedTile->SetSelected(false);
    }

    // Actualizar el tile seleccionado
    selectedTile = tile;

    // Si hay un nuevo tile seleccionado, marcarlo como seleccionado
    if (selectedTile) {
        selectedTile->SetSelected(true);

        // Imprimir las coordenadas del tile seleccionado
        Vector2 position = selectedTile->GetPosition();
        TraceLog(LOG_INFO, "Tile selected at position: (%.0f, %.0f)", position.x, position.y);
    } else {
        // Si no hay tile seleccionado, reiniciar la selección
        selectedTowerIndex = -1;
        buyButtonEnabled = false;
    }
}

EconomySystem& BottomPanel::GetEconomySystem() {
    return economySystem; // Retornar una referencia al sistema de economía
}

void BottomPanel::HandleSelectTower() {
    for (size_t i = 0; i < towerSquares.size(); ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), towerSquares[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedTowerIndex = i; // Seleccionar la torre
        }
    }
}

void BottomPanel::HandleBuy() {
    if (selectedTowerIndex != -1) {
        const TowerInfo& tower = Towers[selectedTowerIndex];
        int cost = tower.costLevel1; // Usar el costo del nivel 1 como ejemplo

        // Habilitar o deshabilitar el botón de compra según el balance
        buyButtonEnabled = (economySystem.GetBalance() >= cost);

        if (buyButtonEnabled && CheckCollisionPointRec(GetMousePosition(), buyButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            economySystem.DecreaseFromBalance(cost); // Reducir el balance
            TraceLog(LOG_INFO, "Bought: %s", tower.name.c_str()); // Imprimir mensaje

            // Reiniciar la selección y deshabilitar los botones
            selectedTowerIndex = -1;
            buyButtonEnabled = false;

            // Deseleccionar el tile seleccionado
            map.UnselectTile(); // Llama a UnselectTile() desde el mapa
        }
    } else {
        buyButtonEnabled = false; // Deshabilitar el botón si no hay torre seleccionada
    }
}