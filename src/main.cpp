#include "raylib.h"
#include "entities/enemies/ogre/Ogre.h"
#include "entities/enemies/harpy/Harpy.h"
#include "entities/enemies/mercenary/Mercenary.h"
#include "entities/enemies/darkElf/DarkElf.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Ogre ogre(true, {25, 25}, 8);
    Harpy harpy(true, {150, 25}, 16);
    Mercenary mercenary(true, {300, 25}, 10);    
    DarkElf darkElf(true, {450, 25}, 12);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    const char *text = "Genetic Kingdom";
    const int fontSize = 20;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        ogre.Update();
        harpy.Update();
        mercenary.Update();
        darkElf.Update();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            ogre.Draw();
            harpy.Draw();
            mercenary.Draw();
            darkElf.Draw();
            // Calculate text width and position it in the center
            int textWidth = MeasureText(text, fontSize);
            int textX = (screenWidth - textWidth) / 2;
            int textY = (screenHeight - fontSize) / 2;

            DrawText(text, textX, textY, fontSize, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}