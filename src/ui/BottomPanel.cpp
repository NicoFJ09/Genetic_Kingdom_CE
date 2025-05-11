#include "BottomPanel.h"
#include "../config/Constants.h"

BottomPanel::BottomPanel(float x, float y, float width, float height, Map& map)
    : bounds({x, y, width, height}),
      selectedTile(nullptr),
      economySystem(),
      towerBuy(map, economySystem, x, y, width, height) { // Inicializar TowerBuy
    // Cargar la textura de la moneda
    coinTexture = LoadTexture("../assets/ui/coin/figueres_coin.png");
}

BottomPanel::~BottomPanel() {
    // Descargar la textura de la moneda
    UnloadTexture(coinTexture);
}

void BottomPanel::Update() {
    if (selectedTile) {
        towerBuy.Update(selectedTile); // Delegar la lógica de compra a TowerBuy
    }
}

void BottomPanel::Draw() {
    DrawRectangleRec(bounds, PEACH_ORANGE); // Dibujar el fondo del panel

    // Configuración del texto y la moneda
    const char* balanceText = TextFormat("Balance: %d", economySystem.GetBalance());
    int fontSize = 20;
    int textWidth = MeasureText(balanceText, fontSize);

    // Posicionar el texto justo a la izquierda del ícono de la moneda
    float coinX = bounds.x + bounds.width - 57; // Posición X del ícono de la moneda
    float coinY = bounds.y + 10;               // Posición Y del ícono de la moneda
    float textX = coinX - textWidth - 10;      // Posición X del texto (10 píxeles de separación)
    float textY = coinY + 15;                       // Alinear verticalmente con la moneda

    DrawText(balanceText, textX, textY, fontSize, BLACK);
    DrawTexture(coinTexture, coinX, coinY, WHITE);

    // Dibujar la UI de compra
    towerBuy.Draw();
}

void BottomPanel::SetSelectedTile(GrassTile* tile) {
    if (selectedTile) {
        selectedTile->SetSelected(false);
    }
    selectedTile = tile;
    if (selectedTile) {
        selectedTile->SetSelected(true);
        towerBuy.Update(selectedTile); // Actualizar TowerBuy con el nuevo tile
    }

    // Actualizar la visibilidad de TowerBuy
    towerBuy.Update(selectedTile);
}

EconomySystem& BottomPanel::GetEconomySystem() {
    return economySystem;
}