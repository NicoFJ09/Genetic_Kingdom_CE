#include "StartScreen.h"

StartScreen::StartScreen(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      title("Genetic Kingdom", 0, 0, 60, 3.0f, (Color){200, 130, 80, 255}, "../assets/fonts/romulus.png"), // Texto más pequeño
      startButton(0, 0, 300, 75, "Start", 30, (Color){200, 130, 80, 255}, "../assets/fonts/romulus.png", 
                  (Color){235, 150, 97, 255}, (Color){245, 170, 110, 255}, (Color){255, 190, 130, 255}) { // Botón más pequeño
    // Centrar el título en la parte superior
    title.Center(screenWidth, screenHeight);
    title.SetPosition(title.GetPosition().x, title.GetPosition().y - 150); // Mover más hacia arriba

    // Centrar el botón debajo del título
    startButton.SetPosition((screenWidth - startButton.GetWidth()) / 2, screenHeight / 2);
}

void StartScreen::Update() {
    // Verificar si el botón fue clickeado
    if (startButton.IsClicked()) {
        TraceLog(LOG_INFO, "Start button clicked!");
        // Aquí puedes cambiar a otra pantalla o iniciar el juego
    }
}

void StartScreen::Draw() {
    ClearBackground((Color){180, 184, 84, 255}); // Fondo color #B4B854
    title.Draw();
    startButton.Draw();
}