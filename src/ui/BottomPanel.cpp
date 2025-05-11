#include "BottomPanel.h"
#include "../config/Constants.h"

BottomPanel::BottomPanel(float x, float y, float width, float height, Map& map)
    : bounds({x, y, width, height}),
      selectedTile(nullptr),
      economySystem(),
      towerBuy(map, economySystem, x, y, width) { // Inicializar TowerBuy
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
    DrawText(balanceText, bounds.x + 10, bounds.y + 10, 20, BLACK);
    DrawTexture(coinTexture, bounds.x + bounds.width - 57, bounds.y + 10, WHITE);

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
    }
}

EconomySystem& BottomPanel::GetEconomySystem() {
    return economySystem;
}