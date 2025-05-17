#include "Projectile.h"

Projectile::Projectile(Vector2 start, Vector2 end, const std::string& type, float speed)
    : position(start), target(end), towerType(type), speed(speed), active(true) {
        TraceLog(LOG_INFO, "Projectile created at (%.2f, %.2f)", position.x, position.y);
    }

void Projectile::Update(float deltaTime) {
    // Si el proyectil no está activo, no hacer nada
    if (!active) return;
    
    Vector2 dir = {target.x - position.x, target.y - position.y};
    float dist = sqrtf(dir.x * dir.x + dir.y * dir.y);
    
    // Si estamos muy cerca del objetivo, considerar que hemos llegado
    if (dist < 2.0f) {
        position = target; // Colocar exactamente en la posición objetivo
        active = false;    // Marcar como inactivo para eliminación
        TraceLog(LOG_INFO, "Projectile reached target and deactivated");
        return;
    }
    
    // Normalizar el vector dirección
    dir.x /= dist;
    dir.y /= dist;
    
    // Mover el proyectil
    float moveDistance = speed * deltaTime;
    
    // Si vamos a sobrepasar el objetivo en este frame, posicionarnos exactamente en el objetivo
    if (moveDistance >= dist) {
        position = target;
        active = false;
        TraceLog(LOG_INFO, "Projectile reached target (distance check) and deactivated");
    } else {
        // Caso normal: avanzar en la dirección calculada
        position.x += dir.x * moveDistance;
        position.y += dir.y * moveDistance;
    }
}

void Projectile::Draw() const {
    // No dibujar si no está activo
    if (!active) return;
    
    // Determinar el color y tamaño según el tipo de proyectil
    Color projColor = BLACK;  // Color por defecto (ataque normal)
    float radius = 4.0f;     // Tamaño por defecto
    
    // Si es un ataque especial (contiene "_special")
    if (towerType.find("_special") != std::string::npos) {
        projColor = RED;
        radius = 6.0f;  // Proyectiles especiales más grandes
    }
    
    // Aplicar variaciones según tipo de torre
    if (towerType.find("Archer") != std::string::npos) {
        // Proyectiles de arquero más pequeños pero más visibles
        radius = radius * 0.8f;
    } else if (towerType.find("Mage") != std::string::npos) {
        // Proyectiles de mago con colores especiales
        projColor = towerType.find("_special") != std::string::npos ? 
                    (Color){220, 20, 60, 255} : // Rojo carmesí para especiales
                    (Color){70, 130, 180, 255}; // Azul acero para normales
    } else if (towerType.find("Artillery") != std::string::npos) {
        // Proyectiles de artillería más grandes
        radius = radius * 1.5f;
        projColor = towerType.find("_special") != std::string::npos ? 
                    (Color){255, 69, 0, 255} : // Rojo-naranja para especiales
                    (Color){128, 128, 128, 255}; // Gris para normales
    }
    
    DrawCircleV(position, radius, projColor);
}