#include "raylib.h"
#include "entities/enemies/ogre/Ogre.h"
#include "entities/enemies/harpy/Harpy.h"
#include "entities/enemies/mercenary/Mercenary.h"
#include "entities/enemies/darkElf/DarkElf.h"
#include "screens/ScreenManager.h"
#include "screens/StartScreen.h"
#include "config/Constants.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Genetic Kingdom");

    // Crear el ScreenManager
    ScreenManager screenManager;

    Ogre ogre(true, {25, 25}, 8);
    Harpy harpy(true, {150, 25}, 16);
    Mercenary mercenary(true, {300, 25}, 10);    
    DarkElf darkElf(true, {450, 25}, 12);

    //--------------------------------------------------------------------------------------
    // Establecer la pantalla inicial
    screenManager.SwitchToScreen(new StartScreen(SCREEN_WIDTH, SCREEN_HEIGHT, &screenManager));

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Actualizar la lógica de la pantalla actual
        screenManager.Update();
        ogre.Update();
        harpy.Update();
        mercenary.Update();
        darkElf.Update();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar la pantalla actual
        screenManager.Draw();
        ogre.Draw();
        harpy.Draw();
        mercenary.Draw();
        darkElf.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}