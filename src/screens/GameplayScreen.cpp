#include "GameplayScreen.h"

// Definir colores al inicio del archivo
static const Color OLIVE_GREEN = (Color){180, 184, 84, 255}; // #B4B854

GameplayScreen::GameplayScreen(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {}

void GameplayScreen::Update() {
    // Por ahora, no hay lógica en la pantalla de juego
}

void GameplayScreen::Draw() {
    ClearBackground(OLIVE_GREEN); // Fondo color OLIVE_GREEN
}