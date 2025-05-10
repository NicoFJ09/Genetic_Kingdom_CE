#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include <string>
#include <vector>

class Enemy {
protected:
    Texture2D texture;       // Textura del enemigo
    Vector2 position;        // Posición del enemigo
    Rectangle frameRec;      // Rectángulo del frame actual
    bool isAlive;            // Estado del enemigo
    int currentFrame;        // Frame actual
    int frameCount;          // Número total de frames
    int frameSpeed;          // Velocidad de animación (frames por segundo)
    int frameCounter;        // Contador de frames
    std::string texturePath; // Ruta de la textura

    const int maxFrameSpeed = 15; // Velocidad máxima de animación
    const int minFrameSpeed = 1;  // Velocidad mínima de animación
    static std::vector<Enemy*> allInstances; // Contenedor estático para todas las instancias
public:

    Enemy(bool alive, Vector2 position, int frameSpeed, const std::string& texturePath, int frameCount);
    virtual ~Enemy();

    virtual void Update();
    virtual void Draw();

    void IncreaseSpeed();
    void DecreaseSpeed();

    static void ClearAllInstances(); // Limpia todas las instancias de enemigos
};

#endif // ENEMY_H