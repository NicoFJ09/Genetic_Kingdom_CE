#include "Game.h"

Game::Game() : waveManager() {
    waveManager.StartWave();
}

Game::Game(float) : waveManager() {  // Ya no usamos waveDuration
    waveManager.StartWave();
}


void Game::Update(float deltaTime) {
    // Spawnear enemigos si hay pendientes y la ola está activa
    if (waveManager.IsWaveActive() && !pendingEnemies.empty()) {
        spawnTimer += deltaTime;
        if (spawnTimer >= spawnInterval) {
            Enemy* next = pendingEnemies.front();
            pendingEnemies.erase(pendingEnemies.begin());
            next->Activate();
            activeEnemies.push_back(next);
            spawnTimer = 0.0f;
        }
    }

    // Actualizar todos los enemigos activos
    for (Enemy* enemy : activeEnemies) {
        enemy->Update(deltaTime);
    }

    // Crear una lista temporal de enemigos que deben eliminarse
    std::vector<Enemy*> enemiesForDeletion;

    // Identificar enemigos que deben eliminarse (completaron su animación de muerte)
    for (Enemy* enemy : activeEnemies) {
        if (enemy->IsMarkedForDeletion()) {
            enemiesForDeletion.push_back(enemy);
        }
    }

    // Eliminar los enemigos marcados del vector de activos
    for (Enemy* enemy : enemiesForDeletion) {
        activeEnemies.erase(
            std::remove(activeEnemies.begin(), activeEnemies.end(), enemy),
            activeEnemies.end()
        );
        
        TraceLog(LOG_INFO, "Removing enemy from activeEnemies after death animation");
    }

    // Eliminar las instancias al final
    for (Enemy* enemy : enemiesForDeletion) {
        delete enemy;
    }

    // Verificar si la ola ha terminado (no hay enemigos activos ni pendientes)
    if (waveManager.IsWaveActive() && activeEnemies.empty() && pendingEnemies.empty()) {
        waveManager.SetWaveCompleted();
    }

    // Actualizar el WaveManager
    waveManager.Update();
}

WaveManager& Game::GetWaveManager() {
    return waveManager;
}

void Game::SpawnEnemiesForWave(const std::vector<Enemy*>& waveEnemies) {
    // Limpiar cualquier pendiente anterior
    for (Enemy* e : pendingEnemies) delete e;
    pendingEnemies.clear();

    // Limpiar activos también (opcional, depende de tu lógica)
    ClearEnemies();

    // Copiar los punteros (en la práctica, deberías clonar o crear nuevos)
    pendingEnemies = waveEnemies;
    spawnTimer = 0.0f;
}

const std::vector<Enemy*>& Game::GetActiveEnemies() const {
    return activeEnemies;
}

void Game::ClearEnemies() {
    // Borrar enemigos activos
    for (Enemy* e : activeEnemies) {
        delete e;
    }
    activeEnemies.clear();
    
    // Borrar enemigos pendientes
    for (Enemy* e : pendingEnemies) {
        delete e;
    }
    pendingEnemies.clear();
    
    spawnTimer = 0.0f;
}