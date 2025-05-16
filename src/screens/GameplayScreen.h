#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.h"
#include "../ui/GamePanel.h"
#include "../ui/BottomPanel.h"
#include "../ui/SidePanel.h"
#include "../core/Game.h"
#include "ScreenManager.h"
#include "../systems/GeneticAlgorithm.h"
#include "../map/BridgeTile.h"
#include "../utils/Timer.h"

class GameplayScreen : public Screen {
private:
    int screenWidth;
    int screenHeight;
    ScreenManager* screenManager; // Agregar puntero al ScreenManager
    GeneticAlgorithm* geneticAlgorithm;

    Game game;
    GamePanel gamePanel;
    BottomPanel bottomPanel;
    SidePanel sidePanel;
    int lastWaveNumber = 0;
    BridgeTile* bridgeTile = nullptr; // Puntero al BridgeTile para detectar colisiones
    
    // Sistema de spawn por etapas
    Timer spawnDelayTimer;
    int spawnStage; // 0: ogres, 1: dark elves, 2: mercenaries, 3: harpies, 4: done
    bool spawningWave;
    std::vector<Enemy*> pendingOgres;
    std::vector<Enemy*> pendingDarkElves;
    std::vector<Enemy*> pendingMercenaries;
    std::vector<Enemy*> pendingHarpies;

    // Métodos para el sistema de spawning
    void PrepareWaveSpawning();
    void UpdateSpawning(float deltaTime);
    
    // Nuevo: método para crear la tanda de enemigos
    std::vector<Enemy*> CreateWaveEnemies();
    
    // Nuevo: método para verificar derrota
    void CheckForDefeat();

public:
    GameplayScreen(int screenWidth, int screenHeight, ScreenManager* screenManager);
    ~GameplayScreen();
    void Update() override;
    void Draw() override;
};

#endif // GAMEPLAY_SCREEN_H