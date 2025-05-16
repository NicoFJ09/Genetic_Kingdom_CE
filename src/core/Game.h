#ifndef GAME_H
#define GAME_H

#include "WaveManager.h"
#include "EconomySystem.h"
#include "../entities/enemies/Enemy.h"
#include "../config/Constants.h"
#include <vector>

class Game {
private:
    WaveManager waveManager;
    EconomySystem* externalEconomySystem = nullptr;
    std::vector<Enemy*> activeEnemies;
    std::vector<Enemy*> pendingEnemies;
    float spawnInterval = 1.0f;
    float spawnTimer = 0.0f;

public:
    Game();
    Game(float);
    void Update(float deltaTime);
    WaveManager& GetWaveManager();
    
    // Establecer el sistema económico externo
    void SetEconomySystem(EconomySystem* system);
    
    void SpawnEnemiesForWave(const std::vector<Enemy*>& waveEnemies);
    const std::vector<Enemy*>& GetActiveEnemies() const;
    void ClearEnemies();
};

#endif // GAME_H