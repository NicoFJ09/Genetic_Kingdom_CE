#include "raylib.h"
#include "screens/ScreenManager.h"
#include "screens/StartScreen.h"
#include "config/Constants.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Genetic Kingdom");

    // Crear el ScreenManager
    ScreenManager screenManager;

    // Establecer la pantalla inicial
    screenManager.SwitchToScreen(new StartScreen(SCREEN_WIDTH, SCREEN_HEIGHT, &screenManager));

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