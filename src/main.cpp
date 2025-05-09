#include "raylib.h"
#include "screens/ScreenManager.h"
#include "screens/StartScreen.h"

int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Genetic Kingdom");

    // Crear el ScreenManager
    ScreenManager screenManager;

    // Establecer la pantalla inicial
    screenManager.SwitchToScreen(new StartScreen(screenWidth, screenHeight, &screenManager));

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Actualizar la lógica de la pantalla actual
        screenManager.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar la pantalla actual
        screenManager.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}