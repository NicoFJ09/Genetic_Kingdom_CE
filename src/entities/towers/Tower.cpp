#include "Tower.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>
#include "../enemies/Enemy.h"
#include <cmath>
#include <memory>

std::vector<Tower*> Tower::allInstances;

Tower::Tower(Vector2 position, int level, const std::string& path, int damage, double speed, int range, int spAttackRegenerationTime)
    : position(position), level(level), texturePath(path), damage(damage), speed(speed), range(range),
       spAttackRegenerationTime(spAttackRegenerationTime), attackTimer(1.0f / speed), 
       spAttackTimer(spAttackRegenerationTime), isSpAttackReady(false)
{
    texture = LoadAndResizeTexture(texturePath.c_str(), 32, 32); // Example width and height
    allInstances.push_back(this);
    attackTimer.Start();
    spAttackTimer.Start();
    
    // Inicializar posición central
    centerPos = {position.x + 16.0f, position.y + 16.0f};
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

float Tower::GetSpecialAttackCooldown() const {
    return spAttackTimer.GetRemainingTime();
}

Vector2 Tower::GetEnemyCenter(Enemy* enemy) {
    if (!enemy) return {0, 0};
    
    // Obtener la posición base del enemigo (esquina superior izquierda)
    Vector2 basePos = enemy->GetPosition();
    
    // Obtener el tamaño del sprite del enemigo a partir de frameRec
    float enemyWidth = 32.0f;   // Ancho por defecto (ajustar según tu juego)
    float enemyHeight = 32.0f;  // Alto por defecto (ajustar según tu juego)
    
    // Calcular las coordenadas centrales
    Vector2 center = {
        basePos.x + enemyWidth / 2.0f,
        basePos.y + enemyHeight / 2.0f
    };
    

    return center;
}


void Tower::PerformSpecialAttack() {
    // Método base que puede ser sobrescrito por clases derivadas
    if (!target) return;
    
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
        
        // Calcular daño real duplicado con resistencia
        float damageMultiplier = 1.0f - (resistance / 100.0f);
        float realDamage = (damage * 2) * damageMultiplier; // DOBLE DAÑO!
        if (realDamage < 0) realDamage = 0;

        // Calcular el centro del sprite del enemigo
        Vector2 enemyCenter = GetEnemyCenter(target);
        
        // Crear un proyectil especial apuntando al centro
        FireAt(enemyCenter, true);

        // Aplicar daño al enemigo
        target->SetHealth(target->GetHealth() - realDamage);

        // Reiniciar temporizador de ataque especial
        isSpAttackReady = false;
        spAttackTimer = Timer(spAttackRegenerationTime);
        spAttackTimer.Start();
        
        // Debug: mostrar info del ataque especial
        TraceLog(LOG_INFO, "SPECIAL ATTACK! %s dealt %.1f damage to %s (%.1f health remaining)", 
               towerType.c_str(), realDamage, target->GetEnemyType().c_str(), target->GetHealth());
    } catch (...) {
        // Si hay error al acceder al target, reiniciar
        target = nullptr;
    }
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
    spAttackTimer.Update(deltaTime);
    
    // Verificar si el ataque especial está listo
    if (!isSpAttackReady && spAttackTimer.IsFinished()) {
        isSpAttackReady = true;
        TraceLog(LOG_INFO, "%s special attack is now ready!", towerType.c_str());
    }

    // Si hay un objetivo y algún tipo de ataque está listo
    if (target) {
        // Priorizar el ataque especial si está disponible
        if (isSpAttackReady) {
            PerformSpecialAttack();
            
            // También reiniciar el timer de ataque normal
            attackTimer = Timer(1.0f / speed);
            attackTimer.Start();
        }
        // Si no hay ataque especial disponible pero el ataque normal está listo
        else if (attackTimer.IsFinished()) {
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

                // Calcular el centro del sprite del enemigo
                Vector2 enemyCenter = GetEnemyCenter(target);
                
                // Crear un proyectil normal apuntando al centro
                FireAt(enemyCenter, false);

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
    
    // Actualizar los proyectiles existentes
    UpdateProjectiles(deltaTime);
}

void Tower::FireAt(const Vector2& targetPos, bool isSpecialAttack) {
    std::string projType = towerType + (isSpecialAttack ? "_special" : "_normal");
    
    // La velocidad del proyectil podría variar según el tipo de torre
    float projSpeed = 300.0f;  // Velocidad base
    
    if (towerType == "Archer Tower") {
        projSpeed = 400.0f;  // Los arqueros disparan más rápido
    } else if (towerType == "Artillery Tower") {
        projSpeed = 200.0f;  // La artillería es más lenta
    }
    
    // Crear el proyectil
    projectiles.push_back(std::make_unique<Projectile>(centerPos, targetPos, projType, projSpeed));
    
    TraceLog(LOG_INFO, "%s firing %s projectile from (%.2f, %.2f) to (%.2f, %.2f)",
             towerType.c_str(),
             isSpecialAttack ? "special" : "normal",
             centerPos.x, centerPos.y,
             targetPos.x, targetPos.y);
}


void Tower::UpdateProjectiles(float deltaTime) {
    // Actualizar todos los proyectiles activos
    for (auto& proj : projectiles) {
        proj->Update(deltaTime);
    }
    
    // Eliminar proyectiles inactivos usando un iterador para mayor claridad
    size_t initialSize = projectiles.size();
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
                      [](const std::unique_ptr<Projectile>& p) { return !p->active; }),
        projectiles.end());
    
    // Registrar cuántos proyectiles se eliminaron
    size_t removed = initialSize - projectiles.size();
    if (removed > 0) {
        TraceLog(LOG_INFO, "Removed %zu inactive projectiles, %zu remaining", 
                 removed, projectiles.size());
    }
}

void Tower::DrawProjectiles() const {
    // Dibujar todos los proyectiles activos
    for (const auto& proj : projectiles) {
        // Verificación adicional para asegurarnos de que solo dibujamos proyectiles activos
        if (proj && proj->active) {
            proj->Draw();
        }
    }
}

// ...

void Tower::Draw() {
    // Dibujar la torre
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
    
    // Dibujar los proyectiles
    DrawProjectiles();
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