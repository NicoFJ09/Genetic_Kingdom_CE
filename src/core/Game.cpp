#include "Game.h"

Game::Game() : waveManager(30.0f) {
    waveManager.StartWave();
}

Game::Game(float waveDuration) : waveManager(waveDuration) {
    waveManager.StartWave();
}

void Game::Update(float deltaTime) {
    waveManager.Update(deltaTime);

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
    // (es importante no modificar el vector mientras lo recorremos)
    std::vector<Enemy*> enemiesForDeletion;

    // Identificar enemigos que deben eliminarse (completaron su animación de muerte)
    for (Enemy* enemy : activeEnemies) {
        if (enemy->IsMarkedForDeletion()) {
            enemiesForDeletion.push_back(enemy);
        }
    }

    // Eliminar los enemigos marcados del vector de activos
    for (Enemy* enemy : enemiesForDeletion) {
        // Eliminar del vector
        activeEnemies.erase(
            std::remove(activeEnemies.begin(), activeEnemies.end(), enemy),
            activeEnemies.end()
        );
        
        // Log de depuración
        TraceLog(LOG_INFO, "Removing enemy from activeEnemies after death animation");
    }

    // Eliminar las instancias al final para evitar acceso inválido
    for (Enemy* enemy : enemiesForDeletion) {
        delete enemy;
    }

    // Si la ola terminó, limpiar enemigos y preparar para la siguiente
    if (!waveManager.IsWaveActive()) {
        ClearEnemies();
    }
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