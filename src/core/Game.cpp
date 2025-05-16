#include "Game.h"
#include "../config/Constants.h"
#include <algorithm>

Game::Game() : waveManager() {
    waveManager.StartWave();
    lastEnemyKilled = false;
    waveEndDelay = 0.0f;
}

Game::Game(float) : waveManager() {
    waveManager.StartWave();
    lastEnemyKilled = false;
    waveEndDelay = 0.0f;
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

    // Eliminar los enemigos marcados del vector de activos y otorgar recompensas
    for (Enemy* enemy : enemiesForDeletion) {
        // Encontrar el valor de recompensa para este tipo de enemigo
        std::string enemyType = enemy->GetEnemyType();
        int reward = 0;
        
        // Buscar el valor de recompensa en las constantes
        for (const auto& info : EnemiesValue) {
            if (info.name == enemyType) {
                reward = info.value;
                break;
            }
        }
        
        // Añadir la recompensa a la economía del jugador
        if (reward > 0 && externalEconomySystem) {
            externalEconomySystem->AddToBalance(reward);
            TraceLog(LOG_INFO, "Received %d coins for killing a %s! New balance: %d", 
                     reward, enemyType.c_str(), externalEconomySystem->GetBalance());
        }
        
        // Incrementar el contador de enemigos eliminados
        waveManager.IncrementEnemiesKilled();
        
        // Eliminar del vector de activos
        activeEnemies.erase(
            std::remove(activeEnemies.begin(), activeEnemies.end(), enemy),
            activeEnemies.end()
        );
        
        TraceLog(LOG_INFO, "Removing enemy %s from activeEnemies after death animation", 
                enemyType.c_str());
    }

    // Eliminar las instancias al final
    for (Enemy* enemy : enemiesForDeletion) {
        delete enemy;
    }

    // Verificar si la ola ha terminado (no hay enemigos activos ni pendientes)
    if (waveManager.IsWaveActive() && activeEnemies.empty() && pendingEnemies.empty()) {
        if (!lastEnemyKilled) {
            // Primera vez que detectamos que no hay enemigos
            lastEnemyKilled = true;
            waveEndDelay = 0.0f;
            TraceLog(LOG_INFO, "Last enemy killed! Starting delay before next wave. Total killed: %d", 
                     waveManager.GetEnemiesKilledInWave());
        } else {
            // Esperar un poco para que se pueda ver el contador final
            waveEndDelay += deltaTime;
            if (waveEndDelay >= 1.5f) {  // Esperar 1.5 segundos
                TraceLog(LOG_INFO, "Wave delay finished. Moving to next wave. Final kill count: %d", 
                         waveManager.GetEnemiesKilledInWave());
                waveManager.SetWaveCompleted();
                lastEnemyKilled = false;
            }
        }
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
    
    // Reiniciar las variables de control para el final de la ola
    lastEnemyKilled = false;
    waveEndDelay = 0.0f;
}

const std::vector<Enemy*>& Game::GetActiveEnemies() const {
    return activeEnemies;
}

void Game::SetEconomySystem(EconomySystem* system) {
    externalEconomySystem = system;
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