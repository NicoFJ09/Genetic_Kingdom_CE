#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include <string>
#include <vector>

class Enemy {
protected:
    // Atributos existentes
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


    // Atributos para path
    std::vector<std::pair<int, int>> path; // Ruta de tiles
    int currentPathIndex = 0;              // Índice actual en la ruta
    float interpolationFactor = 0.0f;      // Progreso entre dos tiles
    Vector2 startPosition;                 // Posición de inicio del segmento
    Vector2 targetPosition;                // Posición objetivo del segmento
    bool isActive = false;                 // Si el enemigo está activo
    const int tileSize = 32;               // Tamaño de tile en píxeles
   
    // Otros atributos
    std::string enemyType;
    int health;
    int speed;
    int arrowResistance;
    int magicResistance;
    int artilleryResistance;
    bool mutated;
    int mutationChance;
    int generation;

public:
    Enemy(bool alive, Vector2 position, int frameSpeed, const std::string& texturePath, int frameCount,
          const std::string& enemyType, int health, int speed, int arrowResistance, int magicResistance,
          int artilleryResistance, bool mutated, int generation, int mutationChance);
    virtual ~Enemy();

    // Getters y setters
    std::string GetEnemyType() const;
    void SetEnemyType(const std::string& type);

    int GetHealth() const;
    void SetHealth(int health);

    int GetSpeed() const;
    void SetSpeed(int speed);

    int GetArrowResistance() const;
    void SetArrowResistance(int resistance);

    int GetMagicResistance() const;
    void SetMagicResistance(int resistance);

    int GetArtilleryResistance() const;
    void SetArtilleryResistance(int resistance);

    bool IsMutated() const;
    void SetMutated(bool mutated);

    int GetGeneration() const;

    int GetMutationChance() const;
    void SetMutationChance(int chance);

    // Métodos para path
    void SetPath(const std::vector<std::pair<int, int>>& newPath);
    void Activate();
    void Deactivate();
    bool IsActive() const;

    // Métodos existentes
    virtual void Update(float deltaTime);
    virtual void Draw();

    void IncreaseSpeed();
    void DecreaseSpeed();

    static void ClearAllInstances(); // Limpia todas las instancias de enemigos

    // Movimiento por path
    void PathMove(float deltaTime);

    // Utilidad
    Vector2 TileToWorldPosition(const std::pair<int, int>& tilePos) const;
};

#endif // ENEMY_H