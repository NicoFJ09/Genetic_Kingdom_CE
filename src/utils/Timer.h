#ifndef TIMER_H
#define TIMER_H

class Timer {
private:
    float duration;    // Duración del temporizador en segundos
    float elapsedTime; // Tiempo transcurrido
    bool running;      // Estado del temporizador

public:
    Timer(float duration = 0.0f);
    void Start();      // Iniciar el temporizador
    void Stop();       // Detener el temporizador
    void Reset();      // Reiniciar el temporizador
    void Update(float deltaTime); // Actualizar el temporizador
    bool IsFinished() const;      // Verificar si el tiempo ha terminado
    float GetRemainingTime() const; // Obtener el tiempo restante
};

#endif // TIMER_H