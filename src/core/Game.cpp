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
            // Spawnear el siguiente enemigo
            Enemy* next = pendingEnemies.front();
            pendingEnemies.erase(pendingEnemies.begin());
            next->Activate();
            activeEnemies.push_back(next);
            spawnTimer = 0.0f;
        }
    }

    // Actualizar enemigos activos
    for (Enemy* enemy : activeEnemies) {
        enemy->Update(deltaTime);
    }

    // Limpiar enemigos que ya no están activos
    activeEnemies.erase(
        std::remove_if(activeEnemies.begin(), activeEnemies.end(),
            [](Enemy* e) { return !e->IsActive(); }),
        activeEnemies.end()
    );

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
    for (Enemy* e : activeEnemies) delete e;
    activeEnemies.clear();
    for (Enemy* e : pendingEnemies) delete e;
    pendingEnemies.clear();
    spawnTimer = 0.0f;
}