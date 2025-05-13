#include "WaveManager.h"

WaveManager::WaveManager(float waveDuration) : currentWave(0), waveTimer(waveDuration), waveActive(false) {}

void WaveManager::StartWave() {
    currentWave++;
    waveTimer.Start();
    waveActive = true;
}

void WaveManager::Update(float deltaTime) {
    if (waveActive) {
        waveTimer.Update(deltaTime);
        if (waveTimer.IsFinished()) {
            waveActive = false; // Terminar la ola actual
            StartWave();        // Iniciar la siguiente ola automáticamente
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