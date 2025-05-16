#include "WaveManager.h"

WaveManager::WaveManager() 
    : currentWave(0), 
      waveActive(false), 
      waveCompleted(false),
      enemiesKilledInWave(0) {}

void WaveManager::StartWave() {
    currentWave++;
    waveActive = true;
    waveCompleted = false;
    enemiesKilledInWave = 0; // Reiniciar el contador de muertes
    
    // Limpiar registro de enemigos para la nueva ola
    enemiesInCurrentWave.clear();
}

void WaveManager::FinishWave() {
    waveActive = false;
    
    // Actualizar las generaciones para todos los enemigos que aparecieron
    for (const auto& enemyType : enemiesInCurrentWave) {
        enemyGenerations[enemyType]++;
    }
}

void WaveManager::Update() {
    // Si la ola está activa y se ha completado (todos los enemigos muertos)
    if (waveActive && waveCompleted) {
        FinishWave();     // Terminar la ola actual y actualizar generaciones
        StartWave();      // Iniciar la siguiente ola automáticamente
    }
}

bool WaveManager::IsWaveActive() const {
    return waveActive;
}

int WaveManager::GetCurrentWave() const {
    return currentWave;
}

bool WaveManager::IsWaveCompleted() const {
    return waveCompleted;
}

void WaveManager::SetWaveCompleted() {
    waveCompleted = true;
}

void WaveManager::IncrementEnemiesKilled() {
    enemiesKilledInWave++;
}

int WaveManager::GetEnemiesKilledInWave() const {
    return enemiesKilledInWave;
}

int WaveManager::GetEnemyGeneration(const std::string& enemyType) {
    // Si el enemigo no existe en el mapa, establecer generación inicial a 1
    if (enemyGenerations.find(enemyType) == enemyGenerations.end()) {
        enemyGenerations[enemyType] = 1;
    }
    return enemyGenerations[enemyType];
}

void WaveManager::RegisterEnemyInWave(const std::string& enemyType) {
    // Registrar que este tipo de enemigo apareció en esta ola
    enemiesInCurrentWave.insert(enemyType);
}

void WaveManager::Reset() {
    currentWave = 0;
    waveActive = false;
    waveCompleted = false;
    enemiesKilledInWave = 0;
    
    // Reiniciar el sistema de generaciones
    enemyGenerations.clear();
    enemiesInCurrentWave.clear();
}