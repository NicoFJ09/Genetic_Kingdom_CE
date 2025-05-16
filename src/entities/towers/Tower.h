#ifndef TOWER_H
#define TOWER_H

#include "raylib.h"
#include <string>
#include <vector>
#include <cstddef>
#include <memory>
#include "Projectile.h"
#include "raymath.h"
#include "../enemies/Enemy.h" 

class Tower {
protected:
    Texture2D texture;            // Textura de la torre
    Vector2 position;             // Posición de la torre
    std::string texturePath;      // Ruta de la textura
    int damage;                   // Daño de la torre
    int level;                    // Nivel de la torre
    int speed;                    // Velocidad de ataque de la torre
    int range;                    // Rango de ataque de la torre
    int spAttackRegenerationTime; // Tiempo de regeneración de ataque especial
    std::string towerType;        // Tipo de torre (Archer, Artillery, Mage)
    static std::vector<Tower*> allInstances; // Contenedor estático para todas las instancias
    virtual void UpdateStats(); // Actualizar estadísticas y sprite según el nivel
    std::vector<std::unique_ptr<Projectile>> projectiles;
    Vector2 centerPos; // Posición central de la torre (para el rango de ataque)

public:
    Tower(Vector2 position, int level, const std::string& texturePath, int damage, int speed, int range, int spAttackRegenerationTime);
    virtual ~Tower();

    virtual void Update(float deltaTime);
    virtual void Draw();

    // Métodos Get para acceder a las características de la torre
    Vector2 GetPosition() const { return position; }
    int GetDamage() const { return damage; }
    int GetLevel() const { return level; }
    int GetSpeed() const { return speed; }
    int GetRange() const { return range; }
    int GetSpecialAttackRegenerationTime() const { return spAttackRegenerationTime; }
    std::string GetTowerType() const { return towerType; }

    void SetPosition(Vector2 pos) { position = pos; }
    Texture2D GetTexture() const { return texture; }
    void SetTexture(const std::string& path);
    Texture2D LoadAndResizeTexture(const std::string& path, int width, int height);

    // Método para subir de nivel
    void LevelUp();
    void AttackEnemy(); //Enemy* targetEnemy

    void FireAt(const Vector2& target);
    void UpdateProjectiles(float deltaTime);
    void DrawProjectiles() const;
};

#endif