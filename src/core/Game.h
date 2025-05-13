#ifndef GAME_H
#define GAME_H

#include "WaveManager.h"

class Game {
private:
    WaveManager waveManager;

public:
    Game(); // Constructor por defecto
    Game(float waveDuration); // Constructor con duración de ola
    void Update(float deltaTime); // Actualizar el estado del juego
    WaveManager& GetWaveManager(); // Obtener el WaveManager
};

#endif // GAME_H