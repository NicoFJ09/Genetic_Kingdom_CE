#include "GameplayScreen.h"
#include "../entities/enemies/ogre/Ogre.h"
#include "../entities/enemies/harpy/Harpy.h"
#include "../entities/enemies/mercenary/Mercenary.h"
#include "../entities/enemies/darkElf/DarkElf.h"
#include "../config/Constants.h"

GameplayScreen::GameplayScreen(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      game(30.0f),
      gamePanel(0, 0, 992, 608),
      sidePanel(992, 0, screenWidth - 992, screenHeight),
      bottomPanel(0, 608, 992, screenHeight - 608, gamePanel.GetMap()) {
    enemies.push_back(new Ogre(true, {25, 25}, 8));
    enemies.push_back(new Harpy(true, {150, 25}, 16));
    enemies.push_back(new Mercenary(true, {300, 25}, 12));
    enemies.push_back(new DarkElf(true, {450, 25}, 10));

    sidePanel.SetActiveEnemies(enemies);

    // Asignar la ruta y activar todos los enemigos
    for (Enemy* enemy : enemies) {
        enemy->SetPath(PATH_SEGMENT);
        enemy->Activate();
    }
}

GameplayScreen::~GameplayScreen() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

void GameplayScreen::Update() {
    float deltaTime = GetFrameTime();
    game.Update(deltaTime);
    gamePanel.Update();
    bottomPanel.Update();

    GrassTile* selectedTile = gamePanel.GetMap().GetSelectedTile();
    TowerTile* selectedTower = gamePanel.GetMap().GetSelectedTower();

    if (selectedTile) {
        bottomPanel.SetSelectedTile(selectedTile);
    } else if (selectedTower) {
        bottomPanel.SetSelectedTower(selectedTower);
    } else {
        bottomPanel.SetSelectedTile(nullptr);
        bottomPanel.SetSelectedTower(nullptr);
    }

    WaveManager& waveManager = game.GetWaveManager();
    sidePanel.UpdateWaveInfo(waveManager.GetCurrentWave(), waveManager.GetRemainingTime());
    sidePanel.Update();

    for (Enemy* enemy : enemies) {
        enemy->Update(deltaTime);
    }

    EconomySystem& economySystem = bottomPanel.GetEconomySystem();
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