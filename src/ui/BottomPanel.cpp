#include "BottomPanel.h"
#include "../config/Constants.h"

BottomPanel::BottomPanel(float x, float y, float width, float height, Map& map)
    : bounds({x, y, width, height}),
      selectedTile(nullptr),
      selectedTower(nullptr),
      economySystem(),
      towerBuy(map, economySystem, x, y, width, height),
      towerUpgrade(x, y, width, height, economySystem) { // Inicializar TowerUpgrade
    // Cargar la textura de la moneda
    coinTexture = LoadTexture("../assets/ui/coin/figueres_coin.png");
}

BottomPanel::~BottomPanel() {
    // Descargar la textura de la moneda
    UnloadTexture(coinTexture);
}

void BottomPanel::Update() {
    if (selectedTile) {
        towerBuy.Update(selectedTile); // Actualizar TowerBuy si hay un GrassTile seleccionado
    } else if (selectedTower) {
        towerUpgrade.Update(selectedTower); // Actualizar TowerUpgrade si hay un TowerTile seleccionado
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

    if (selectedTile) {
        towerBuy.Draw(); // Dibujar TowerBuy si hay un GrassTile seleccionado
    } else if (selectedTower) {
        towerUpgrade.Draw(selectedTower); // Dibujar TowerUpgrade si hay un TowerTile seleccionado
    }
}

void BottomPanel::SetSelectedTile(GrassTile* tile) {
    // Deseleccionar el TowerTile actual si hay uno seleccionado
    if (selectedTower) {
        selectedTower = nullptr;
    }

    // Manejar la selección del GrassTile
    if (selectedTile) {
        selectedTile->SetSelected(false);
    }
    selectedTile = tile;
    if (selectedTile) {
        selectedTile->SetSelected(true);
        towerBuy.Update(selectedTile); // Actualizar TowerBuy con el nuevo tile
    }
}

void BottomPanel::SetSelectedTower(TowerTile* tower) {
    // Deseleccionar el GrassTile actual si hay uno seleccionado
    if (selectedTile) {
        selectedTile->SetSelected(false); // Cambiar el estado del tile a no seleccionado
        selectedTile = nullptr;          // Establecer el puntero a nullptr
    }

    // Actualizar el puntero de la torre seleccionada
    selectedTower = tower;

    if (selectedTower) {
        towerUpgrade.Update(selectedTower); // Actualizar TowerUpgrade con la nueva torre
    }
}

EconomySystem& BottomPanel::GetEconomySystem() {
    return economySystem;
}