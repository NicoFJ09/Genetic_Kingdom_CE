#include "GameplayScreen.h"
#include "../entities/enemies/ogre/Ogre.h"
#include "../entities/enemies/harpy/Harpy.h"
#include "../entities/enemies/mercenary/Mercenary.h"
#include "../entities/enemies/darkElf/DarkElf.h"
#include "../config/Constants.h"
#include "../systems/Pathfinding.h"

std::vector<Enemy*> GameplayScreen::CreateWaveEnemies() {
    std::vector<Enemy*> waveEnemies;
    WaveManager& waveManager = game.GetWaveManager();
    
    // Ogre
    std::string ogreType = "Ogre";
    waveManager.RegisterEnemyInWave(ogreType);
    int ogreGen = waveManager.GetEnemyGeneration(ogreType);
    waveEnemies.push_back(new Ogre(true, {25, 25}, 8, ogreGen));
    
    // Harpy
    std::string harpyType = "Harpy";
    waveManager.RegisterEnemyInWave(harpyType);
    int harpyGen = waveManager.GetEnemyGeneration(harpyType);
    waveEnemies.push_back(new Harpy(true, {150, 25}, 16, harpyGen));
    
    // Mercenary
    std::string mercType = "Mercenary";
    waveManager.RegisterEnemyInWave(mercType);
    int mercGen = waveManager.GetEnemyGeneration(mercType);
    waveEnemies.push_back(new Mercenary(true, {300, 25}, 12, mercGen));
    
    // DarkElf (dos instancias, misma generación)
    std::string darkElfType = "DarkElf";
    waveManager.RegisterEnemyInWave(darkElfType);
    int darkElfGen = waveManager.GetEnemyGeneration(darkElfType);
    waveEnemies.push_back(new DarkElf(true, {450, 25}, 10, darkElfGen));
    waveEnemies.push_back(new DarkElf(true, {450, 25}, 10, darkElfGen));
    
    auto PATH_SEGMENT = AStarPath(0, 0, 18, 30, GAME_MAP);
    for (Enemy* enemy : waveEnemies) {
        enemy->SetPath(PATH_SEGMENT);
    }
    return waveEnemies;
}

GameplayScreen::GameplayScreen(int screenWidth, int screenHeight, ScreenManager* screenManager)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      game(30.0f),
      gamePanel(0, 0, 992, 608),
      sidePanel(992, 0, screenWidth - 992, screenHeight),
      bottomPanel(0, 608, 992, screenHeight - 608, gamePanel.GetMap()) 
{
    // Crear y pasar la primera tanda de enemigos
    std::vector<Enemy*> waveEnemies = CreateWaveEnemies();
    game.SpawnEnemiesForWave(waveEnemies);
    // Mostrar los primeros enemigos en el panel
    sidePanel.SetActiveEnemies(game.GetActiveEnemies());
}

GameplayScreen::~GameplayScreen() {
    // Game se encarga de limpiar enemigos
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

    EconomySystem& economySystem = bottomPanel.GetEconomySystem();

    // --- NUEVO: Detectar el inicio de una nueva ola ---
    int currentWave = waveManager.GetCurrentWave();
    if (currentWave != lastWaveNumber) {
        lastWaveNumber = currentWave;

        std::vector<Enemy*> waveEnemies = CreateWaveEnemies();
        game.SpawnEnemiesForWave(waveEnemies);
        sidePanel.SetActiveEnemies(waveEnemies); // Muestra SOLO los nuevos
    }
}

void GameplayScreen::Draw() {
    gamePanel.Draw();
    bottomPanel.Draw();
    sidePanel.Draw();

    // Dibujar los enemigos activos
    for (Enemy* enemy : game.GetActiveEnemies()) {
        enemy->Draw();
    }
}