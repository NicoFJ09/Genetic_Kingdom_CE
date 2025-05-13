#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "../utils/Timer.h"

class WaveManager {
private:
    int currentWave; // Número de la ola actual
    Timer waveTimer; // Temporizador para manejar la duración de cada ola
    bool waveActive; // Estado de la ola actual

public:
    WaveManager(float waveDuration);
    void StartWave();       // Iniciar una nueva ola
    void Update(float deltaTime); // Actualizar el estado de la ola
    bool IsWaveActive() const;    // Verificar si la ola está activa
    int GetCurrentWave() const;   // Obtener el número de la ola actual
    float GetRemainingTime() const; // Obtener el tiempo restante de la ola
};

#endif // WAVE_MANAGER_H