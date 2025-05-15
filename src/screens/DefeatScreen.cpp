#include "DefeatScreen.h"
#include "StartScreen.h"
#include "../config/Constants.h"

DefeatScreen::DefeatScreen(int screenWidth, int screenHeight, ScreenManager* screenManager)
    : screenWidth(screenWidth), screenHeight(screenHeight), screenManager(screenManager),
      title("DEFEATED!", 0, 0, 60, 3.0f, RUST_ORANGE, Romulus),
      backButton(0, 0, 400, 75, "Back to Main Menu", 30, RUST_ORANGE, Romulus, 
                  PEACH_ORANGE, APRICOT, LIGHT_TANGERINE) {
    // Centrar el título en la parte superior
    title.Center(screenWidth, screenHeight);
    title.SetPosition(title.GetPosition().x, title.GetPosition().y - 150);

    // Centrar el botón debajo del título
    backButton.SetPosition((screenWidth - backButton.GetWidth()) / 2, screenHeight / 2);
}

DefeatScreen::~DefeatScreen() {}

void DefeatScreen::Update() {
    if (backButton.IsClicked()) {
        // Cambiar a la pantalla de juego
        screenManager->SwitchToScreen(new StartScreen(screenWidth, screenHeight, screenManager));
    }
}

void DefeatScreen::Draw() {
    // Dibujar el fondo
    ClearBackground(OLIVE_GREEN);

    // Dibujar el título y el botón
    title.Draw();
    backButton.Draw();
}