#include "GameplayScreen.h"
#include "../config/Constants.h"

GameplayScreen::GameplayScreen(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      gamePanel(0, 0, 992, 608),
      sidePanel(992, 0, screenWidth - 992, screenHeight),
      bottomPanel(0, 608, 992, screenHeight - 608, gamePanel.GetMap()) {}

void GameplayScreen::Update() {
    gamePanel.Update();
    bottomPanel.Update();

    // Obtener el tile seleccionado del mapa
    GrassTile* selectedTile = gamePanel.GetMap().GetSelectedTile();
    TowerTile* selectedTower = gamePanel.GetMap().GetSelectedTower();

    // Actualizar el BottomPanel según el tipo de selección
    if (selectedTile) {
        bottomPanel.SetSelectedTile(selectedTile); // Si hay un GrassTile seleccionado
    } else if (selectedTower) {
        bottomPanel.SetSelectedTower(selectedTower); // Si hay un TowerTile seleccionado
    }

    // Obtener el sistema de economía (si es necesario)
    EconomySystem& economySystem = bottomPanel.GetEconomySystem();
}

void GameplayScreen::Draw() {
    gamePanel.Draw();
    bottomPanel.Draw();
    sidePanel.Draw();
}