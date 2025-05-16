#include "Tower.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>
#include "../enemies/Enemy.h"
#include <cmath>

std::vector<Tower*> Tower::allInstances;

Tower::Tower(Vector2 position, int level, const std::string& path, int damage, double speed, int range, int spAttackRegenerationTime)
    : position(position), level(level), texturePath(path), damage(damage), speed(speed), range(range),
       spAttackRegenerationTime(spAttackRegenerationTime), attackTimer(1.0f / speed)
{
    texture = LoadAndResizeTexture(texturePath.c_str(), 32, 32); // Example width and height
    allInstances.push_back(this);
    attackTimer.Start();
}

Texture2D Tower::LoadAndResizeTexture(const std::string& path, int width, int height) {
    Image img = LoadImage(path.c_str());
    if (img.data == nullptr) {
        TraceLog(LOG_ERROR, "Failed to load image: %s", path.c_str());
        return {0}; // Retornar una textura inválida
    }
    ImageResize(&img, width, height);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

Tower::~Tower() {
    if (texture.id != 0) {
        UnloadTexture(texture);
    }
    
    // Eliminar de la lista estática
    auto it = std::find(allInstances.begin(), allInstances.end(), this);
    if (it != allInstances.end()) {
        allInstances.erase(it);
    }
}

bool Tower::IsEnemyInRange(const Enemy* enemy) const {
    // Primero verificar que el puntero no sea nulo
    if (!enemy) return false;
    
    // Verificar si el enemigo está activo para fines de juego
    // Un enemigo en animación de muerte ya NO es un objetivo válido
    if (!enemy->IsActive() || enemy->IsDying()) return false;
    
    // Finalmente calcular la distancia
    float dx = enemy->GetPosition().x - position.x;
    float dy = enemy->GetPosition().y - position.y;
    float distance = sqrtf(dx * dx + dy * dy);
    return distance <= (range * 32.0f); // range en tiles * tamaño del tile
}

Enemy* Tower::FindFirstEnemyInRange() const {
    for (Enemy* enemy : Enemy::GetAllInstances()) {
        // Asegúrate de que el enemigo no sea nulo y esté en rango
        if (enemy && IsEnemyInRange(enemy)) {
            return enemy;
        }
    }
    return nullptr;
}

Enemy* Tower::FindClosestEnemyInRange() const {
    Enemy* closest = nullptr;
    float minDist = 1e9f;
    
    // Crear una copia local del vector para evitar problemas
    const auto& enemies = Enemy::GetAllInstances();
    
    for (Enemy* enemy : enemies) {
        // Evitar acceso a puntero nulo
        if (!enemy) continue;
        
        if (IsEnemyInRange(enemy)) {
            float dx = enemy->GetPosition().x - position.x;
            float dy = enemy->GetPosition().y - position.y;
            float dist = sqrtf(dx * dx + dy * dy);
            if (dist < minDist) {
                minDist = dist;
                closest = enemy;
            }
        }
    }
    return closest;
}
void Tower::Update(float deltaTime)
{
    // Verificar si el target sigue siendo válido
    if (target) {
        try {
            // Intenta acceder al target para verificar si es válido
            // Un enemigo que está muriendo ya no es un objetivo válido
            bool isValid = target->IsActive() && !target->IsDying() && IsEnemyInRange(target);
            if (!isValid) {
                target = nullptr;
            }
        } catch (...) {
            // Si ocurre cualquier excepción, el target podría haber sido liberado
            target = nullptr;
        }
    }
    
    // Si no hay target válido, buscar uno nuevo
    if (!target) {
        target = FindClosestEnemyInRange();
    }

    // Actualizar temporizador de ataque
    attackTimer.Update(deltaTime);

    if (target && attackTimer.IsFinished()) {
        try {
            // Determinar resistencia según tipo de torre
            int resistance = 0;
            if (towerType == "Archer Tower") {
                resistance = target->GetArrowResistance();
            } else if (towerType == "Mage Tower") {
                resistance = target->GetMagicResistance();
            } else if (towerType == "Artillery Tower") {
                resistance = target->GetArtilleryResistance();
            }
            
            // Calcular daño real considerando resistencia
            float damageMultiplier = 1.0f - (resistance / 100.0f);
            float realDamage = damage * damageMultiplier;
            if (realDamage < 0) realDamage = 0;

            // Aplicar daño al enemigo
            target->SetHealth(target->GetHealth() - realDamage);

            // Reiniciar el timer para el próximo ataque
            attackTimer = Timer(1.0f / speed);
            attackTimer.Start();
            
            // Debug: mostrar info del ataque
            TraceLog(LOG_INFO, "%s attacked target %s for %.1f damage (%.1f health remaining)", 
                   towerType.c_str(), target->GetEnemyType().c_str(), realDamage, target->GetHealth());
        } catch (...) {
            // Si hay error al acceder al target, reiniciar
            target = nullptr;
        }
    }
}


void Tower::Draw()
{
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}

void Tower::SetTexture(const std::string& path)
{
    UnloadTexture(texture);
    texture = LoadTexture(path.c_str());
    texturePath = path;
}

void Tower::LevelUp() {
    const int maxLevel = 3; // Nivel máximo permitido
    if (level < maxLevel) {
        level++; // Incrementar el nivel
        UpdateStats(); // Actualizar estadísticas y sprite
        TraceLog(LOG_INFO, "Tower leveled up to level %d", level);
    }
}

void Tower::UpdateStats() {
    // Este método será sobrescrito por las clases derivadas
    TraceLog(LOG_WARNING, "UpdateStats() should be implemented in derived classes.");
}