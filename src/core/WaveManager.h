#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include <string>
#include <unordered_map>
#include <set>

class WaveManager {
private:
    int currentWave;       // Número de la ola actual
    bool waveActive;       // Estado de la ola actual
    bool waveCompleted;    // Indica si la ola actual ha sido completada
    
    // Sistema de generaciones de enemigos
    std::unordered_map<std::string, int> enemyGenerations; // Mapa de tipo de enemigo -> generación
    std::set<std::string> enemiesInCurrentWave;            // Enemigos que aparecieron en esta ola

public:
    WaveManager();
    void StartWave();       // Iniciar una nueva ola
    void FinishWave();      // Finalizar la ola actual y actualizar generaciones
    void Update();          // Actualizar el estado de la ola (ya no usa deltaTime)
    bool IsWaveActive() const;    // Verificar si la ola está activa
    int GetCurrentWave() const;   // Obtener el número de la ola actual
    bool IsWaveCompleted() const; // Verificar si la ola actual se completó
    void SetWaveCompleted();      // Marcar la ola como completada
    
    // Métodos para el sistema de generaciones
    int GetEnemyGeneration(const std::string& enemyType); // Obtener generación actual de un tipo
    void RegisterEnemyInWave(const std::string& enemyType); // Registrar aparición en la ola actual
    void Reset(); // Reiniciar el sistema para nueva partida
};

#endif // WAVE_MANAGER_H