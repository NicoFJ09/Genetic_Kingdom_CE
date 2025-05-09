#include "raylib.h"
#include "ui/Button.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Genetic Kingdom - Button Example");

    // Crear un botón con texto
    Button myButton(300, 200, 200, 50, "Click Me", 20, BLACK, "../assets/fonts/romulus.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar el botón
        myButton.Draw();

        // Verificar si el botón fue clickeado
        if (myButton.IsClicked()) {
            DrawText("Button Clicked!", 10, 10, 20, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}