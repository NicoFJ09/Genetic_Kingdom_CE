#include "raylib.h"
#include "screens/StartScreen.h" // Incluir la pantalla de inicio

int main(void) {
    const int screenWidth = 1280; // Nueva resolución
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Genetic Kingdom");

    // Crear la pantalla de inicio
    StartScreen startScreen(screenWidth, screenHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Actualizar la lógica de la pantalla
        startScreen.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar la pantalla
        startScreen.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}