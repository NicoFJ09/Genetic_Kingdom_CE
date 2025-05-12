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

    // Pasar el tile seleccionado al BottomPanel
    GrassTile* selectedTile = gamePanel.GetMap().GetSelectedTile();
    TowerTile* selectedTower = gamePanel.GetMap().GetSelectedTower();
    bottomPanel.SetSelectedTile(selectedTile);
    bottomPanel.SetSelectedTower(selectedTower);
    EconomySystem& economySystem = bottomPanel.GetEconomySystem();
}

void GameplayScreen::Draw() {
    gamePanel.Draw();
    bottomPanel.Draw();
    sidePanel.Draw();
}