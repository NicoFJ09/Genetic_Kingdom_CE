#include "GameplayScreen.h"
#include "../entities/enemies/ogre/Ogre.h"
#include "../entities/enemies/harpy/Harpy.h"
#include "../entities/enemies/mercenary/Mercenary.h"
#include "../entities/enemies/darkElf/DarkElf.h"

GameplayScreen::GameplayScreen(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      game(30.0f), // Inicializar el juego con una duración de ola de 30 segundos
      gamePanel(0, 0, 992, 608),
      sidePanel(992, 0, screenWidth - 992, screenHeight),
      bottomPanel(0, 608, 992, screenHeight - 608, gamePanel.GetMap()) {
    // Crear enemigos dinámicamente y almacenarlos en el contenedor local
    enemies.push_back(new Ogre(true, {25, 25}, 8));
    enemies.push_back(new Harpy(true, {150, 25}, 16));
    enemies.push_back(new Mercenary(true, {300, 25}, 12));
    enemies.push_back(new DarkElf(true, {450, 25}, 10));

    // Pasar las instancias de enemigos al SidePanel
    sidePanel.SetActiveEnemies(enemies);
}

GameplayScreen::~GameplayScreen() {
    // Liberar memoria de los enemigos
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear(); // Vaciar el contenedor
}

void GameplayScreen::Update() {
    float deltaTime = GetFrameTime(); // Obtener el tiempo entre frames
    game.Update(deltaTime);          // Actualizar el estado del juego
    gamePanel.Update();
    bottomPanel.Update();

    // Pasar la información de la ola al SidePanel
    WaveManager& waveManager = game.GetWaveManager();
    sidePanel.UpdateWaveInfo(waveManager.GetCurrentWave(), waveManager.GetRemainingTime());

    // Actualizar las entidades
    for (Enemy* enemy : enemies) {
        enemy->Update();
    }
}

void GameplayScreen::Draw() {
    gamePanel.Draw();
    bottomPanel.Draw();
    sidePanel.Draw(); // Dibujar el SidePanel

    // Dibujar las entidades
    for (Enemy* enemy : enemies) {
        enemy->Draw();
    }
}