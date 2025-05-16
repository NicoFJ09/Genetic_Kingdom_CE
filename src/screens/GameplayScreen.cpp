#include "GameplayScreen.h"
#include "DefeatScreen.h"
#include "../entities/enemies/ogre/Ogre.h"
#include "../entities/enemies/harpy/Harpy.h"
#include "../entities/enemies/mercenary/Mercenary.h"
#include "../entities/enemies/darkElf/DarkElf.h"
#include "../config/Constants.h"
#include "../systems/Pathfinding.h"
#include "../systems/GeneticAlgorithm.h"


std::vector<Enemy*> GameplayScreen::CreateWaveEnemies() {
    std::vector<Enemy*> waveEnemies;
    WaveManager& waveManager = game.GetWaveManager();
    std::vector<Enemy*> ogres;
    std::vector<Enemy*> harpies;
    std::vector<Enemy*> mercenaries;
    std::vector<Enemy*> darkElves;
    

    int numOgres = GetRandomValue(5, 15);
    int numHarpies = GetRandomValue(5, 15);
    int numMercenaries = GetRandomValue(5, 15);
    int numDarkElves = GetRandomValue(5, 15);

    

    // Ogre
    std::string ogreType = "Ogre";
    waveManager.RegisterEnemyInWave(ogreType);
    int ogreGen = waveManager.GetEnemyGeneration(ogreType);
    
    std::string harpyType = "Harpy";
    waveManager.RegisterEnemyInWave(harpyType);
    int harpyGen = waveManager.GetEnemyGeneration(harpyType);
    
    std::string mercType = "Mercenary";
    waveManager.RegisterEnemyInWave(mercType);
    int mercGen = waveManager.GetEnemyGeneration(mercType);
    
    std::string darkElfType = "Dark Elf";
    waveManager.RegisterEnemyInWave(darkElfType);
    int darkElfGen = waveManager.GetEnemyGeneration(darkElfType);
    
    auto PATH_SEGMENT = AStarPath(0, 0, 18, 30, GAME_MAP);

    // Generar Ogres
    for (int i = 0; i < numOgres; i++) {
        Vector2 position = {25.0f + i * 10.0f, 25.0f};
        Ogre* ogre = new Ogre(true, false, position, 8, ogreGen);
        ogre->SetPath(PATH_SEGMENT);
        ogres.push_back(ogre);
        waveEnemies.push_back(ogre); // También añadir al vector general
    }
    
    // Generar Harpies
    for (int i = 0; i < numHarpies; i++) {
        Vector2 position = {150.0f + i * 10.0f, 25.0f};
        Harpy* harpy = new Harpy(true, false, position, 16, harpyGen);
        harpy->SetPath(PATH_SEGMENT);
        harpies.push_back(harpy);
        waveEnemies.push_back(harpy);
    }
    
    // Generar Mercenaries
    for (int i = 0; i < numMercenaries; i++) {
        Vector2 position = {300.0f + i * 10.0f, 25.0f};
        Mercenary* mercenary = new Mercenary(true, false, position, 12, mercGen);
        mercenary->SetPath(PATH_SEGMENT);
        mercenaries.push_back(mercenary);
        waveEnemies.push_back(mercenary);
    }
    
    // Generar DarkElves
    for (int i = 0; i < numDarkElves; i++) {
        Vector2 position = {450.0f + i * 10.0f, 25.0f};
        DarkElf* darkElf = new DarkElf(true, false, position, 10, darkElfGen);
        darkElf->SetPath(PATH_SEGMENT);
        darkElves.push_back(darkElf);
        waveEnemies.push_back(darkElf);
    }
    
    // DEBUG: Mostrar información sobre los enemigos generados
    TraceLog(LOG_INFO, "Wave %d created: %d Ogres, %d Harpies, %d Mercenaries, %d DarkElves", 
             waveManager.GetCurrentWave(), numOgres, numHarpies, numMercenaries, numDarkElves);
    
    // Pasar los vectores específicos al algoritmo genético (solo para preparar estructura)
    if (geneticAlgorithm) {
        geneticAlgorithm->setEnemyVectors(ogres, harpies, mercenaries, darkElves);
        geneticAlgorithm->printGenerationSummary(waveManager.GetCurrentWave());
    }
    
    return waveEnemies;
}

GameplayScreen::GameplayScreen(int screenWidth, int screenHeight, ScreenManager* screenManager)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      screenManager(screenManager),
      game(),
      gamePanel(0, 0, 992, 608),
      sidePanel(992, 0, screenWidth - 992, screenHeight),
      bottomPanel(0, 608, 992, screenHeight - 608, gamePanel.GetMap()) 
{
    // Inicializar el algoritmo genético (tamaño de población y tasa de mutación)
    geneticAlgorithm = new GeneticAlgorithm(40, 0.1f);
    
    game.SetEconomySystem(&bottomPanel.GetEconomySystem());
    
    // Obtener referencia al BridgeTile
    auto& map = gamePanel.GetMap();
    for (int y = 0; y < map.GetHeight(); y++) {
        for (int x = 0; x < map.GetWidth(); x++) {
            Tile* tile = map.GetTile(x, y);
            BridgeTile* bridge = dynamic_cast<BridgeTile*>(tile);
            if (bridge) {
                bridgeTile = bridge;
                TraceLog(LOG_INFO, "Found bridge tile at position (%d, %d)", x, y);
                break;
            }
        }
        if (bridgeTile) break;
    }
    
    // Crear y pasar la primera tanda de enemigos
    std::vector<Enemy*> waveEnemies = CreateWaveEnemies();
    game.SpawnEnemiesForWave(waveEnemies);
    
    // Extraer los vectores por tipo para el panel lateral
    std::vector<Enemy*> ogres, harpies, mercenaries, darkElves;
    for (Enemy* enemy : game.GetActiveEnemies()) {
        std::string type = enemy->GetEnemyType();
        if (type == "Ogre") {
            ogres.push_back(enemy);
        } else if (type == "Harpy") {
            harpies.push_back(enemy);
        } else if (type == "Mercenary") {
            mercenaries.push_back(enemy);
        } else if (type == "Dark Elf") {
            darkElves.push_back(enemy);
        }
    }
    
    // Inicializar el panel con los vectores específicos
    sidePanel.SetEnemyVectors(ogres, harpies, mercenaries, darkElves);
}

GameplayScreen::~GameplayScreen() {
    // Game se encarga de limpiar enemigos
    Enemy::ClearAllInstances();
    
    // Liberar el algoritmo genético
    if (geneticAlgorithm) {
        delete geneticAlgorithm;
        geneticAlgorithm = nullptr;
    }
}

void GameplayScreen::CheckForDefeat() {
    // Verifica si hay un puente y si algún enemigo ha llegado a él
    if (bridgeTile && bridgeTile->IsUnderAttack(game.GetActiveEnemies())) {
        TraceLog(LOG_WARNING, "DEFEAT! Enemy reached the bridge!");
        
        // Cambiar a la pantalla de derrota
        if (screenManager) {
            screenManager->SwitchToScreen(new DefeatScreen(screenWidth, screenHeight, screenManager));
        }
    }
}

void GameplayScreen::Update() {
    float deltaTime = GetFrameTime();
    
    // Verificar derrota antes de actualizar el juego
    CheckForDefeat();
    
    game.Update(deltaTime);
    gamePanel.Update();
    bottomPanel.Update();

    // --- ACTUALIZAR TODAS LAS TORRES ---
    auto& map = gamePanel.GetMap();
    for (int y = 0; y < map.GetHeight(); ++y) {
        for (int x = 0; x < map.GetWidth(); ++x) {
            TowerTile* towerTile = dynamic_cast<TowerTile*>(map.GetTile(x, y));
            if (towerTile && towerTile->GetTower()) {
                Tower* tower = towerTile->GetTower();
                tower->Update(deltaTime);
            }
        }
    }

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
    sidePanel.UpdateWaveInfo(
        waveManager.GetCurrentWave(),
        waveManager.GetEnemiesKilledInWave() // Pasar el contador
    );
    sidePanel.Update();

    EconomySystem& economySystem = bottomPanel.GetEconomySystem();

    // --- NUEVO: Detectar el inicio de una nueva ola ---
    int currentWave = waveManager.GetCurrentWave();
    if (currentWave != lastWaveNumber) {
        lastWaveNumber = currentWave;

        std::vector<Enemy*> waveEnemies = CreateWaveEnemies();
        game.SpawnEnemiesForWave(waveEnemies);
        
        // Extraer los vectores específicos por tipo:
        std::vector<Enemy*> ogres, harpies, mercenaries, darkElves;
        
        for (Enemy* enemy : game.GetActiveEnemies()) {
            std::string type = enemy->GetEnemyType();
            if (type == "Ogre") {
                ogres.push_back(enemy);
            } else if (type == "Harpy") {
                harpies.push_back(enemy);
            } else if (type == "Mercenary") {
                mercenaries.push_back(enemy);
            } else if (type == "Dark Elf") {
                darkElves.push_back(enemy);
            }
        }
        
        // Actualizar el panel lateral con los vectores específicos
        sidePanel.SetEnemyVectors(ogres, harpies, mercenaries, darkElves);
    }
    
    // Actualizamos el panel lateral con los enemigos activos
    // Extraer los vectores específicos por tipo cada actualización
    std::vector<Enemy*> ogres, harpies, mercenaries, darkElves;
    
    for (Enemy* enemy : game.GetActiveEnemies()) {
        std::string type = enemy->GetEnemyType();
        if (type == "Ogre") {
            ogres.push_back(enemy);
        } else if (type == "Harpy") {
            harpies.push_back(enemy);
        } else if (type == "Mercenary") {
            mercenaries.push_back(enemy);
        } else if (type == "Dark Elf") {
            darkElves.push_back(enemy);
        }
    }
    
    // Actualizar el panel lateral con los vectores específicos
    sidePanel.SetEnemyVectors(ogres, harpies, mercenaries, darkElves);
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