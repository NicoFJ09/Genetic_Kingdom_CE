#include "Game.h"

// Constructor por defecto
Game::Game() : waveManager(30.0f) { // Duración predeterminada de 30 segundos
    waveManager.StartWave(); // Iniciar la primera ola
}

// Constructor con duración de ola
Game::Game(float waveDuration) : waveManager(waveDuration) {
    waveManager.StartWave(); // Iniciar la primera ola
}

void Game::Update(float deltaTime) {
    waveManager.Update(deltaTime);
}

WaveManager& Game::GetWaveManager() {
    return waveManager;
}