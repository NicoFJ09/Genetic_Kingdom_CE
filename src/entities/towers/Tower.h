#ifndef TOWER_H
#define TOWER_H

#include "raylib.h"
#include <string>
#include <vector>
#include <memory>
#include "../enemies/Enemy.h" 
#include "../../utils/Timer.h"
#include "Projectile.h"

class Tower {
protected:
    Texture2D texture;            // Textura de la torre
    Vector2 position;             // Posición de la torre
    Vector2 centerPos;            // Posición central de la torre (para disparos)
    std::string texturePath;      // Ruta de la textura
    int damage;                   // Daño de la torre
    int level;                    // Nivel de la torre
    double speed;                 // Velocidad de ataque de la torre
    int range;                    // Rango de ataque de la torre
    int spAttackRegenerationTime; // Tiempo de regeneración de ataque especial
    std::string towerType;        // Tipo de torre (Archer, Artillery, Mage)
    static std::vector<Tower*> allInstances; // Contenedor estático para todas las instancias
    Enemy* target = nullptr;      // Objetivo actual
    virtual void UpdateStats();   // Actualizar estadísticas y sprite según el nivel

    Enemy* FindFirstEnemyInRange() const;
    Enemy* FindClosestEnemyInRange() const;
    bool IsEnemyInRange(const Enemy* enemy) const;
    Timer attackTimer;            // Temporizador para ataques normales
    Timer spAttackTimer;          // Temporizador para ataques especiales
    bool isSpAttackReady;         // Indica si el ataque especial está listo
    
    // Sistema de proyectiles
    std::vector<std::unique_ptr<Projectile>> projectiles;
    void FireAt(const Vector2& targetPos, bool isSpecialAttack);
    void UpdateProjectiles(float deltaTime);
    void DrawProjectiles() const;
    Vector2 GetEnemyCenter(Enemy* enemy);

public:
    Tower(Vector2 position, int level, const std::string& texturePath, int damage, double speed, int range, int spAttackRegenerationTime);
    virtual ~Tower();

    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void PerformSpecialAttack(); // Método que pueden sobrescribir las torres específicas

    // Métodos Get para acceder a las características de la torre
    Vector2 GetPosition() const { return position; }
    int GetDamage() const { return damage; }
    int GetLevel() const { return level; }
    double GetSpeed() const { return speed; }
    int GetRange() const { return range; }
    int GetSpecialAttackRegenerationTime() const { return spAttackRegenerationTime; }
    std::string GetTowerType() const { return towerType; }
    Enemy* GetTarget() const { return target; }
    void SetTarget(Enemy* newTarget) { target = newTarget; }
    bool IsSpecialAttackReady() const { return isSpAttackReady; }
    float GetSpecialAttackCooldown() const; // Devuelve el tiempo restante en segundos

    void SetPosition(Vector2 pos) { 
        position = pos; 
        centerPos = {position.x + 16.0f, position.y + 16.0f}; // Actualizar posición central
    }
    Texture2D GetTexture() const { return texture; }
    void SetTexture(const std::string& path);
    Texture2D LoadAndResizeTexture(const std::string& path, int width, int height);

    // Método para subir de nivel
    void LevelUp();
};

#endif