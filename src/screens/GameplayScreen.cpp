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
    int currentWave = waveManager.GetCurrentWave();
    
    // Vectores separados por tipo de enemigo
    std::vector<Enemy*> ogres;
    std::vector<Enemy*> harpies;
    std::vector<Enemy*> mercenaries;
    std::vector<Enemy*> darkElves;

    auto PATH_SEGMENT = AStarPath(0, 0, 18, 30, GAME_MAP);

    // Actualizar todas las probabilidades de mutación al inicio de la oleada
    if (geneticAlgorithm) {
        geneticAlgorithm->updateMutationChanceForType("Ogre");
        if (currentWave >= 2) geneticAlgorithm->updateMutationChanceForType("Dark Elf");
        if (currentWave >= 3) geneticAlgorithm->updateMutationChanceForType("Mercenary");
        if (currentWave >= 4) geneticAlgorithm->updateMutationChanceForType("Harpy");

        TraceLog(LOG_INFO, "Probabilidades de mutación actualizadas para la oleada %d", currentWave);
    }

    // --- Ogres (aparecen desde la primera ola) ---
    if (currentWave >= 1) {
        std::string ogreType = "Ogre";
        waveManager.RegisterEnemyInWave(ogreType);
        int ogreGen = waveManager.GetEnemyGeneration(ogreType);
        
        // Obtener la probabilidad de mutación actualizada
        int ogreMutationChance = geneticAlgorithm->getMutationChanceForType(ogreType);
        
        if (ogreGen == 1) {
            int numOgres = GetRandomValue(5, 15);
            TraceLog(LOG_INFO, "Spawning %d Ogres randomly (Generation 1) with mutation chance %d%%", 
                    numOgres, ogreMutationChance);
            
            for (int i = 0; i < numOgres; i++) {
                Vector2 position = {25.0f + i * 10.0f, 25.0f};
                // Pasar mutationChance directamente al constructor
                Ogre* ogre = new Ogre(true, false, position, 8, ogreGen, ogreMutationChance);
                ogre->SetPath(PATH_SEGMENT);
                ogres.push_back(ogre);
                waveEnemies.push_back(ogre);
            }
        } else {
            TraceLog(LOG_INFO, "Usando genes evolucionados para Ogros (Generación %d) con probabilidad de mutación %d%%", 
                    ogreGen, ogreMutationChance);
            
            std::vector<EnemyGenes> genes = geneticAlgorithm->getNextGenGenes();
            int numOgres = genes.empty() ? 10 : genes.size();
            
            for (int i = 0; i < numOgres; i++) {
                Vector2 position = {25.0f + i * 10.0f, 25.0f};
                // Pasar mutationChance directamente al constructor
                Ogre* ogre = new Ogre(true, false, position, 8, ogreGen, ogreMutationChance);
                
                if (!genes.empty() && i < static_cast<int>(genes.size())) {
                    ogre->SetHealth(genes[i].health);
                    ogre->SetSpeed(genes[i].speed);
                    ogre->SetArrowResistance(genes[i].arrowResistance);
                    ogre->SetMagicResistance(genes[i].magicResistance);
                    ogre->SetArtilleryResistance(genes[i].artilleryResistance);
                    ogre->SetMutated(genes[i].mutated);
                    if (ogre->IsMutated()) {
                        ogre->SetTexture("../assets/textures/enemies/ogre/OgreMoveSpriteSheet_mutated.png");
                    }
                    
                    TraceLog(LOG_INFO, "Ogro %d: Vida=%.1f, Vel=%.1f, ResF=%d, ResM=%d, ResA=%d, Mutado=%s",
                           i, genes[i].health, genes[i].speed, (int)genes[i].arrowResistance, 
                           (int)genes[i].magicResistance, (int)genes[i].artilleryResistance,
                           genes[i].mutated ? "Sí" : "No");
                }
                
                ogre->SetPath(PATH_SEGMENT);
                ogres.push_back(ogre);
                waveEnemies.push_back(ogre);
            }
        }
    }
    
    // --- Dark Elves (aparecen desde la ola 2) ---
    if (currentWave >= 2) {
        std::string darkElfType = "Dark Elf";
        waveManager.RegisterEnemyInWave(darkElfType);
        int darkElfGen = waveManager.GetEnemyGeneration(darkElfType);
        
        // Obtener la probabilidad de mutación actualizada
        int darkElfMutationChance = geneticAlgorithm->getMutationChanceForType(darkElfType);

        if (darkElfGen == 1) {
            int numDarkElves = GetRandomValue(5, 15);
            TraceLog(LOG_INFO, "Spawning %d Dark Elves randomly (Generation 1) with mutation chance %d%%", 
                    numDarkElves, darkElfMutationChance);
            
            for (int i = 0; i < numDarkElves; i++) {
                Vector2 position = {450.0f + i * 10.0f, 25.0f};
                // Pasar mutationChance directamente al constructor
                DarkElf* darkElf = new DarkElf(true, false, position, 10, darkElfGen, darkElfMutationChance);
                darkElf->SetPath(PATH_SEGMENT);
                darkElves.push_back(darkElf);
                waveEnemies.push_back(darkElf);
            }
        } else {
            TraceLog(LOG_INFO, "Usando genes evolucionados para Elfos Oscuros (Generación %d) con probabilidad de mutación %d%%", 
                    darkElfGen, darkElfMutationChance);
            
            std::vector<EnemyGenes> genes = geneticAlgorithm->getNextGenGenes();
            int numDarkElves = genes.empty() ? 10 : genes.size();
            
            for (int i = 0; i < numDarkElves; i++) {
                Vector2 position = {450.0f + i * 10.0f, 25.0f};
                // Pasar mutationChance directamente al constructor
                DarkElf* darkElf = new DarkElf(true, false, position, 10, darkElfGen, darkElfMutationChance);
                
                if (!genes.empty() && i < static_cast<int>(genes.size())) {
                    darkElf->SetHealth(genes[i].health);
                    darkElf->SetSpeed(genes[i].speed);
                    darkElf->SetArrowResistance(genes[i].arrowResistance);
                    darkElf->SetMagicResistance(genes[i].magicResistance);
                    darkElf->SetArtilleryResistance(genes[i].artilleryResistance);
                    darkElf->SetMutated(genes[i].mutated);
                    if (darkElf->IsMutated()) {
                        darkElf->SetTexture("../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet_mutated.png");
                    }
                }
                
                darkElf->SetPath(PATH_SEGMENT);
                darkElves.push_back(darkElf);
                waveEnemies.push_back(darkElf);
            }
        }
    }
    
    // --- Mercenarios (aparecen desde la ola 3) ---
    if (currentWave >= 3) {
        std::string mercType = "Mercenary";
        waveManager.RegisterEnemyInWave(mercType);
        int mercGen = waveManager.GetEnemyGeneration(mercType);
        
        // Obtener la probabilidad de mutación actualizada
        int mercMutationChance = geneticAlgorithm->getMutationChanceForType(mercType);

        if (mercGen == 1) {
            int numMercenaries = GetRandomValue(5, 15);
            TraceLog(LOG_INFO, "Spawning %d Mercenaries randomly (Generation 1) with mutation chance %d%%", 
                    numMercenaries, mercMutationChance);
            
            for (int i = 0; i < numMercenaries; i++) {
                Vector2 position = {300.0f + i * 10.0f, 25.0f};
                // Pasar mutationChance directamente al constructor
                Mercenary* mercenary = new Mercenary(true, false, position, 12, mercGen, mercMutationChance);
                mercenary->SetPath(PATH_SEGMENT);
                mercenaries.push_back(mercenary);
                waveEnemies.push_back(mercenary);
            }
        } else {
            TraceLog(LOG_INFO, "Usando genes evolucionados para Mercenarios (Generación %d) con probabilidad de mutación %d%%", 
                    mercGen, mercMutationChance);
            
            std::vector<EnemyGenes> genes = geneticAlgorithm->getNextGenGenes();
            int numMercenaries = genes.empty() ? 10 : genes.size();
            
            for (int i = 0; i < numMercenaries; i++) {
                Vector2 position = {300.0f + i * 10.0f, 25.0f};
                // Pasar mutationChance directamente al constructor
                Mercenary* mercenary = new Mercenary(true, false, position, 12, mercGen, mercMutationChance);
                
                if (!genes.empty() && i < static_cast<int>(genes.size())) {
                    mercenary->SetHealth(genes[i].health);
                    mercenary->SetSpeed(genes[i].speed);
                    mercenary->SetArrowResistance(genes[i].arrowResistance);
                    mercenary->SetMagicResistance(genes[i].magicResistance);
                    mercenary->SetArtilleryResistance(genes[i].artilleryResistance);
                    mercenary->SetMutated(genes[i].mutated);
                    if (mercenary->IsMutated()) {
                        mercenary->SetTexture("../assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet_mutated.png");
                    }
                }
                
                mercenary->SetPath(PATH_SEGMENT);
                mercenaries.push_back(mercenary);
                waveEnemies.push_back(mercenary);
            }
        }
    }

    // --- Arpías (aparecen desde la ola 4) ---
    if (currentWave >= 4) {
        std::string harpyType = "Harpy";
        waveManager.RegisterEnemyInWave(harpyType);
        int harpyGen = waveManager.GetEnemyGeneration(harpyType);
        
        // Obtener la probabilidad de mutación actualizada
        int harpyMutationChance = geneticAlgorithm->getMutationChanceForType(harpyType);

        if (harpyGen == 1) {
            int numHarpies = GetRandomValue(5, 15);
            TraceLog(LOG_INFO, "Spawning %d Harpies randomly (Generation 1) with mutation chance %d%%", 
                    numHarpies, harpyMutationChance);
            
            for (int i = 0; i < numHarpies; i++) {
                Vector2 position = {150.0f + i * 10.0f, 25.0f};
                // Pasar mutationChance directamente al constructor
                Harpy* harpy = new Harpy(true, false, position, 16, harpyGen, harpyMutationChance);
                harpy->SetPath(PATH_SEGMENT);
                harpies.push_back(harpy);
                waveEnemies.push_back(harpy);
            }
        } else {
            TraceLog(LOG_INFO, "Usando genes evolucionados para Arpías (Generación %d) con probabilidad de mutación %d%%", 
                    harpyGen, harpyMutationChance);
            
            std::vector<EnemyGenes> genes = geneticAlgorithm->getNextGenGenes();
            int numHarpies = genes.empty() ? 10 : genes.size();
            
            for (int i = 0; i < numHarpies; i++) {
                Vector2 position = {150.0f + i * 10.0f, 25.0f};
                // Pasar mutationChance directamente al constructor
                Harpy* harpy = new Harpy(true, false, position, 16, harpyGen, harpyMutationChance);
                
                if (!genes.empty() && i < static_cast<int>(genes.size())) {
                    harpy->SetHealth(genes[i].health);
                    harpy->SetSpeed(genes[i].speed);
                    harpy->SetArrowResistance(genes[i].arrowResistance);
                    harpy->SetMagicResistance(genes[i].magicResistance);
                    harpy->SetArtilleryResistance(genes[i].artilleryResistance);
                    harpy->SetMutated(genes[i].mutated);
                    if (harpy->IsMutated()) {
                        harpy->SetTexture("../assets/textures/enemies/harpy/HarpyMoveSpriteSheet_mutated.png");
                    }
                }
                
                harpy->SetPath(PATH_SEGMENT);
                harpies.push_back(harpy);
                waveEnemies.push_back(harpy);
            }
        }
    }

    // DEBUG: Mostrar información sobre los enemigos generados
    TraceLog(LOG_INFO, "Wave %d created: %zu Ogres, %zu Harpies, %zu Mercenaries, %zu DarkElves", 
             waveManager.GetCurrentWave(), ogres.size(), harpies.size(), mercenaries.size(), darkElves.size());
    
    // Procesar tipos para evolución (sin actualizar la probabilidad de mutación, que ya fue actualizada arriba)
    if (geneticAlgorithm) {
        // IMPORTANTE: Modificamos processEnemyType en GeneticAlgorithm para evitar múltiples actualizaciones
        // de la probabilidad de mutación. La actualización ya ocurrió al inicio de esta función.
        
        // Procesar ogros
        if (!ogres.empty()) {
            geneticAlgorithm->processEnemyType(ogres, "Ogre", false); // No actualizar probabilidad (ya actualizada)
            geneticAlgorithm->printTypeSummary(waveManager.GetCurrentWave());
            int ogreGen = ogres[0]->GetGeneration();
            if (ogreGen > 1) {
                TraceLog(LOG_INFO, "Evolucionando población de Ogros para la próxima generación");
                geneticAlgorithm->evolveCurrentType();
            }
        }
        
        // Procesar arpías
        if (!harpies.empty()) {
            geneticAlgorithm->processEnemyType(harpies, "Harpy", false); // No actualizar probabilidad (ya actualizada)
            geneticAlgorithm->printTypeSummary(waveManager.GetCurrentWave());
            int harpyGen = harpies[0]->GetGeneration();
            if (harpyGen > 1) {
                TraceLog(LOG_INFO, "Evolucionando población de Arpías para la próxima generación");
                geneticAlgorithm->evolveCurrentType();
            }
        }
        
        // Procesar mercenarios
        if (!mercenaries.empty()) {
            geneticAlgorithm->processEnemyType(mercenaries, "Mercenary", false); // No actualizar probabilidad (ya actualizada)
            geneticAlgorithm->printTypeSummary(waveManager.GetCurrentWave());
            int mercGen = mercenaries[0]->GetGeneration();
            if (mercGen > 1) {
                TraceLog(LOG_INFO, "Evolucionando población de Mercenarios para la próxima generación");
                geneticAlgorithm->evolveCurrentType();
            }
        }
        
        // Procesar elfos oscuros
        if (!darkElves.empty()) {
            geneticAlgorithm->processEnemyType(darkElves, "Dark Elf", false); // No actualizar probabilidad (ya actualizada)
            geneticAlgorithm->printTypeSummary(waveManager.GetCurrentWave());
            int darkElfGen = darkElves[0]->GetGeneration();
            if (darkElfGen > 1) {
                TraceLog(LOG_INFO, "Evolucionando población de Elfos Oscuros para la próxima generación");
                geneticAlgorithm->evolveCurrentType();
            }
        }
    }
    
    return waveEnemies;
}

GameplayScreen::GameplayScreen(int screenWidth, int screenHeight, ScreenManager* screenManager)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      screenManager(screenManager),
      game(),
      gamePanel(0, 0, 992, 608),
      bottomPanel(0, 608, 992, screenHeight - 608, gamePanel.GetMap()),
      sidePanel(992, 0, screenWidth - 992, screenHeight)
{
    // Inicializar el algoritmo genético (tamaño de población y tasa de mutación)
    geneticAlgorithm = new GeneticAlgorithm(GetRandomValue(5, 15), 0.1f);
    
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