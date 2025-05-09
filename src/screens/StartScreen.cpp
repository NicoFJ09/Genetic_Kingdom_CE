#include "StartScreen.h"
#include "GameplayScreen.h"

// Definir colores al inicio del archivo
static const Color OLIVE_GREEN = (Color){180, 184, 84, 255};         // #B4B854
static const Color RUST_ORANGE = (Color){200, 130, 80, 255};         // #C88250
static const Color PEACH_ORANGE = (Color){235, 150, 97, 255};        // #EB9661
static const Color APRICOT = (Color){245, 170, 110, 255};            // #F5AA6E
static const Color LIGHT_TANGERINE = (Color){255, 190, 130, 255};    // #FFBE82

StartScreen::StartScreen(int screenWidth, int screenHeight, ScreenManager* screenManager)
    : screenWidth(screenWidth), screenHeight(screenHeight), screenManager(screenManager),
      title("Genetic Kingdom", 0, 0, 60, 3.0f, RUST_ORANGE, "../assets/fonts/romulus.png"), // Texto color RUST_ORANGE
      startButton(0, 0, 300, 75, "Start", 30, RUST_ORANGE, "../assets/fonts/romulus.png", 
                  PEACH_ORANGE, APRICOT, LIGHT_TANGERINE) { // Botón con colores PEACH_ORANGE, APRICOT y LIGHT_TANGERINE
    // Centrar el título en la parte superior
    title.Center(screenWidth, screenHeight);
    title.SetPosition(title.GetPosition().x, title.GetPosition().y - 150); // Mover más hacia arriba

    // Centrar el botón debajo del título
    startButton.SetPosition((screenWidth - startButton.GetWidth()) / 2, screenHeight / 2);
}

void StartScreen::Update() {
    // Verificar si el botón fue clickeado
    if (startButton.IsClicked()) {
        // Cambiar a la pantalla de juego
        screenManager->SwitchToScreen(new GameplayScreen(screenWidth, screenHeight));
    }
}

void StartScreen::Draw() {
    ClearBackground(OLIVE_GREEN); // Fondo color OLIVE_GREEN
    title.Draw();
    startButton.Draw();
}