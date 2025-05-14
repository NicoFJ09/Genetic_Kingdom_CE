#ifndef GAME_H
#define GAME_H

#include "WaveManager.h"
#include "../entities/enemies/Enemy.h"
#include <vector>

class Game {
private:
    WaveManager waveManager;
    std::vector<Enemy*> activeEnemies;   // Enemigos actualmente en el mapa
    std::vector<Enemy*> pendingEnemies;  // Enemigos por spawnear en la ola actual
    float spawnInterval = 1.0f;          // Tiempo entre spawns (puedes ajustar)
    float spawnTimer = 0.0f;             // Timer para el siguiente spawn

public:
    Game(); // Constructor por defecto
    Game(float waveDuration); // Constructor con duración de ola

    void Update(float deltaTime); // Actualizar el estado del juego
    WaveManager& GetWaveManager(); // Obtener el WaveManager

    // Nuevo: preparar la ola con los enemigos a spawnear
    void SpawnEnemiesForWave(const std::vector<Enemy*>& waveEnemies);

    // Nuevo: acceso a los enemigos activos
    const std::vector<Enemy*>& GetActiveEnemies() const;

    // Limpieza de enemigos al finalizar la ola
    void ClearEnemies();
};

#endif // GAME_H