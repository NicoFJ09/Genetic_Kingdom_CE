#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "../utils/Timer.h"
#include <string>
#include <unordered_map>
#include <set>

class WaveManager {
private:
    int currentWave; // Número de la ola actual
    Timer waveTimer; // Temporizador para manejar la duración de cada ola
    bool waveActive; // Estado de la ola actual
    
    // Sistema de generaciones de enemigos
    std::unordered_map<std::string, int> enemyGenerations; // Mapa de tipo de enemigo -> generación
    std::set<std::string> enemiesInCurrentWave; // Enemigos que aparecieron en esta ola

public:
    WaveManager(float waveDuration);
    void StartWave();       // Iniciar una nueva ola
    void FinishWave();      // Finalizar la ola actual y actualizar generaciones
    void Update(float deltaTime); // Actualizar el estado de la ola
    bool IsWaveActive() const;    // Verificar si la ola está activa
    int GetCurrentWave() const;   // Obtener el número de la ola actual
    float GetRemainingTime() const; // Obtener el tiempo restante de la ola
    
    // Métodos para el sistema de generaciones
    int GetEnemyGeneration(const std::string& enemyType); // Obtener generación actual de un tipo
    void RegisterEnemyInWave(const std::string& enemyType); // Registrar aparición en la ola actual
    void Reset(); // Reiniciar el sistema para nueva partida
};

#endif // WAVE_MANAGER_H