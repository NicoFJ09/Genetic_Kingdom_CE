#include "WaveManager.h"

WaveManager::WaveManager(float waveDuration) : currentWave(0), waveTimer(waveDuration), waveActive(false) {}

void WaveManager::StartWave() {
    currentWave++;
    waveTimer.Start();
    waveActive = true;
    
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

void WaveManager::Update(float deltaTime) {
    if (waveActive) {
        waveTimer.Update(deltaTime);
        if (waveTimer.IsFinished()) {
            FinishWave();     // Terminar la ola actual y actualizar generaciones
            StartWave();      // Iniciar la siguiente ola automáticamente
        }
    }
}

bool WaveManager::IsWaveActive() const {
    return waveActive;
}

int WaveManager::GetCurrentWave() const {
    return currentWave;
}

float WaveManager::GetRemainingTime() const {
    return waveTimer.GetRemainingTime();
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
    waveTimer.Reset();
    
    // Reiniciar el sistema de generaciones
    enemyGenerations.clear();
    enemiesInCurrentWave.clear();
}