#include "GameplayScreen.h"
#include "../config/Constants.h" // Incluir las constantes de colores y dimensiones

GameplayScreen::GameplayScreen(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      gamePanel(0, 0, 992, 608), // Panel principal
      sidePanel(992, 0, screenWidth - 992, screenHeight), // Panel lateral
      bottomPanel(0, 608, 992, screenHeight - 608) { // Panel inferior
}

void GameplayScreen::Update() {
    // Actualizar lógica de los paneles
    gamePanel.Update();
    bottomPanel.Update();
    
    // Pasar el tile seleccionado al BottomPanel
    GrassTile* selectedTile = gamePanel.GetMap().GetSelectedTile();
    bottomPanel.SetSelectedTile(selectedTile);
}

void GameplayScreen::Draw() {
    // Dibujar los paneles
    gamePanel.Draw();
    bottomPanel.Draw();
    sidePanel.Draw();
}