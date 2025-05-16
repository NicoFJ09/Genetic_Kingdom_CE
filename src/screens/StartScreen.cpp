#include "StartScreen.h"
#include "GameplayScreen.h"
#include "../config/Constants.h"
#include "raylib.h"

StartScreen::StartScreen(int screenWidth, int screenHeight, ScreenManager* screenManager)
    : screenWidth(screenWidth), screenHeight(screenHeight), screenManager(screenManager),
      title("Genetic Kingdom", 0, 0, 60, 3.0f, RUST_ORANGE, Romulus),
      startButton(0, 0, 300, 75, "Start", 30, RUST_ORANGE, Romulus, 
                  PEACH_ORANGE, APRICOT, LIGHT_TANGERINE) {
    // Centrar el título en la parte superior
    title.Center(screenWidth, screenHeight);
    title.SetPosition(title.GetPosition().x, title.GetPosition().y - 150);

    // Centrar el botón debajo del título
    startButton.SetPosition((screenWidth - startButton.GetWidth()) / 2, screenHeight / 2);
    InitAudioDevice();
    music = LoadMusicStream("../assets/music/xDeviruchi - And The Journey Begins (Intro).mp3"); // <-- assign to member
    PlayMusicStream(music);
    float timePlayed = 0.0f;        // Time played normalized [0.0f..1.0f]
    bool pause = false;             // Music playing paused
    UpdateMusicStream(music);   // Update music buffer with new stream data
    // Get normalized time played for current music stream
    timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);
    if (timePlayed > 1.0f) timePlayed = 1.0f;   // Make sure time played is no longer than music

}

StartScreen::~StartScreen() {
    CloseAudioDevice(); 
    UnloadMusicStream(music);   // Unload music stream buffers from RAM        
}

void StartScreen::Update() {
    if (startButton.IsClicked()) {
        // Cambiar a la pantalla de juego
        screenManager->SwitchToScreen(new GameplayScreen(screenWidth, screenHeight, screenManager));
    }
}

void StartScreen::Draw() {
    // Dibujar el fondo
    ClearBackground(OLIVE_GREEN);

    // Dibujar el título y el botón
    title.Draw();
    startButton.Draw();
}