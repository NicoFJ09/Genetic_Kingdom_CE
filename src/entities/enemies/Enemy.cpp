#include "Enemy.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>

// Inicialización del contenedor estático
std::vector<Enemy*> Enemy::allInstances;

Enemy::Enemy(bool alive, Vector2 pos, int frameSpeed, const std::string& texturePath, int frameCount,
             const std::string& enemyType, double health, double speed, int arrowResistance,
             int magicResistance, int artilleryResistance, bool mutated, int generation, int mutationChance)
    : isAlive(alive), position(pos), frameSpeed(frameSpeed > 0 ? frameSpeed : 1), currentFrame(0), frameCounter(0),
      frameCount(frameCount), texturePath(texturePath), enemyType(enemyType), health(health), speed(speed),
      arrowResistance(arrowResistance), magicResistance(magicResistance), artilleryResistance(artilleryResistance),
      mutated(mutated), mutationChance(mutationChance),generation(generation),
      currentPathIndex(0), interpolationFactor(0.0f), isActive(false),
      isDying(false), deathTimer(0.0f), toDelete(false) {

    // Guardar rutas de texturas para movimiento y muerte
    moveTexturePath = texturePath;
    
    // Detectar ruta de muerte automáticamente
    size_t lastSlash = texturePath.find_last_of('/');
    size_t lastDot = texturePath.find_last_of('.');
    if (lastSlash != std::string::npos && lastDot != std::string::npos && lastDot > lastSlash) {
        std::string base = texturePath.substr(0, lastSlash + 1);
        std::string name = texturePath.substr(lastSlash + 1, lastDot - lastSlash - 1);
        std::string ext = texturePath.substr(lastDot);
        
        // Reemplazar "Move" por "Death" en el nombre del archivo
        size_t movePos = name.find("Move");
        if (movePos != std::string::npos) {
            name.replace(movePos, 4, "Death");
        }
        deathTexturePath = base + name + ext;
    } else {
        deathTexturePath = texturePath; // fallback
    }

    // Cargar la textura inicial
    texture = LoadTexture(texturePath.c_str());
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture: %s", texturePath.c_str());
        frameRec = {0.0f, 0.0f, 0.0f, 0.0f};
    } else {
        frameRec = {0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height};
    }
    
    // Registrar esta instancia
    allInstances.push_back(this);
}

Enemy::~Enemy() {
    if (texture.id != 0) {
        UnloadTexture(texture);
    }
    // Eliminar la instancia del contenedor estático
    auto it = std::find(allInstances.begin(), allInstances.end(), this);
    if (it != allInstances.end()) {
        allInstances.erase(it);
    }
}

// Getters y setters
std::string Enemy::GetEnemyType() const {
    return enemyType;
}
void Enemy::SetEnemyType(const std::string& type) {
    enemyType = type;
}

double Enemy::GetHealth() const {
    return health;
}

void Enemy::SetHealth(double healthValue) {
    health = healthValue;
    if (health <= 0 && isAlive && !isDying) {
        Kill();
    }
}

double Enemy::GetSpeed() const {
    return speed;
}

void Enemy::SetSpeed(double speedValue) {
    speed = speedValue;
}

int Enemy::GetArrowResistance() const {
    return arrowResistance;
}

void Enemy::SetArrowResistance(int resistance) {
    arrowResistance = resistance;
}

int Enemy::GetMagicResistance() const {
    return magicResistance;
}

void Enemy::SetMagicResistance(int resistance) {
    magicResistance = resistance;
}

int Enemy::GetArtilleryResistance() const {
    return artilleryResistance;
}

void Enemy::SetArtilleryResistance(int resistance) {
    artilleryResistance = resistance;
}

bool Enemy::IsMutated() const {
    return mutated;
}

void Enemy::SetMutated(bool mutatedValue) {
    mutated = mutatedValue;
}

int Enemy::GetGeneration() const {
    return generation;
}

void Enemy::SetMutationChance(int chance) {
    mutationChance = chance;
}

int Enemy::GetMutationChance() const {
    return mutationChance;
}

// Métodos para path
void Enemy::SetPath(const std::vector<std::pair<int, int>>& newPath) {
    path.clear();
    path.reserve(newPath.size());
    // Invertir el orden de cada par: (fila, columna) -> (columna, fila)
    for (const auto& tile : newPath) {
        path.emplace_back(tile.second, tile.first);
    }
    currentPathIndex = 0;
    interpolationFactor = 0.0f;
    if (path.size() > 1) {
        startPosition = TileToWorldPosition(path[0]);
        targetPosition = TileToWorldPosition(path[1]);
        position = startPosition;
    }
}

void Enemy::Activate() {
    isActive = true;
    isAlive = true;
    if (!path.empty()) {
        position = TileToWorldPosition(path[0]);
        currentPathIndex = 0;
        interpolationFactor = 0.0f;
        if (path.size() > 1) {
            startPosition = TileToWorldPosition(path[0]);
            targetPosition = TileToWorldPosition(path[1]);
        }
    }
}

void Enemy::Deactivate() {
    isActive = false;
}

bool Enemy::IsActive() const {
    return isActive;
}

Vector2 Enemy::TileToWorldPosition(const std::pair<int, int>& tilePos) const {
    return {
        static_cast<float>(tilePos.first * tileSize),
        static_cast<float>(tilePos.second * tileSize)
    };
}
void Enemy::PathMove(float deltaTime) {
    if (!isActive || path.size() < 2) return;
    if (currentPathIndex >= (int)path.size() - 1) {
        Deactivate();
        return;
    }

    // Calcular dirección entre startPosition y targetPosition
    Vector2 dir = {
        targetPosition.x - startPosition.x,
        targetPosition.y - startPosition.y
    };
    float distance = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (distance == 0) return;
    dir.x /= distance;
    dir.y /= distance;

    // Avanzar según la velocidad y el deltaTime (5 veces más rápido)
    float moveAmount = speed * deltaTime * 5.0f;
    interpolationFactor += moveAmount / distance;

    if (interpolationFactor >= 1.0f) {
        // Llegamos al siguiente punto
        currentPathIndex++;
        if (currentPathIndex >= (int)path.size() - 1) {
            position = TileToWorldPosition(path.back());
            Deactivate();
            return;
        }
        startPosition = TileToWorldPosition(path[currentPathIndex]);
        targetPosition = TileToWorldPosition(path[currentPathIndex + 1]);
        interpolationFactor = 0.0f;
    }

    // Interpolación lineal entre startPosition y targetPosition
    position.x = startPosition.x + (targetPosition.x - startPosition.x) * interpolationFactor;
    position.y = startPosition.y + (targetPosition.y - startPosition.y) * interpolationFactor;
}

// Métodos existentes
void Enemy::Update(float deltaTime) {
    if (isDying) {
        deathTimer.Update(deltaTime);
        // Avanzar frames de muerte
        frameCounter++;
        if (frameCounter >= (60 / frameSpeed)) {
            frameCounter = 0;
            if (currentFrame < frameCount - 1) {
                currentFrame++;
                frameRec.x = (float)currentFrame * frameRec.width;
            }
        }
        if (deathTimer.IsFinished()) {
            toDelete = true;
        }
        return;
    }

    if (!isAlive) return;

    PathMove(deltaTime);

    if (frameSpeed <= 0) {
        TraceLog(LOG_ERROR, "Invalid frameSpeed: %d", frameSpeed);
        frameSpeed = 1; // Valor por defecto
    }

    frameCounter++;
    if (frameCounter >= (60 / frameSpeed)) {
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % frameCount;
        frameRec.x = (float)currentFrame * frameRec.width;
    }
}

void Enemy::Kill() {
    // Nada que hacer si ya está muriendo
    if (isDying) return;
    
    TraceLog(LOG_INFO, "Killing %s at position (%.0f, %.0f)", enemyType.c_str(), position.x, position.y);
    
    // Cambiar estados
    isAlive = false;
    isActive = false;  // Ya no está activo para juego
    isDying = true;    // Pero está en animación de muerte
    
    // Preparar la ruta de la textura de muerte
    std::string deathTexPath = deathTexturePath;
    
    // Si el enemigo está mutado, modificar la ruta para usar la versión mutada
    if (mutated) {
        // Buscar la posición del último punto (antes de la extensión)
        size_t lastDot = deathTexPath.find_last_of('.');
        if (lastDot != std::string::npos) {
            // Insertar "_mutated" antes de la extensión
            deathTexPath.insert(lastDot, "_mutated");
            TraceLog(LOG_INFO, "Using mutated death texture: %s", deathTexPath.c_str());
        }
    }
    
    // Descargar la textura actual y cargar la de muerte (mutada o normal)
    if (texture.id != 0) UnloadTexture(texture);
    texture = LoadTexture(deathTexPath.c_str());
    
    // Configurar los parámetros de la animación de muerte
    if (texture.id != 0) {
        // Configurar el número de frames para la animación de muerte según tipo
        if (enemyType == "Harpy") {
            frameCount = 7;
        } else if (enemyType == "Dark Elf") {
            frameCount = 7;
        } else {
            frameCount = 4; // Default para otros tipos
        }
        
        frameRec = {0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height};
    } else {
        TraceLog(LOG_ERROR, "Failed to load death texture: %s", deathTexPath.c_str());
    }
    
    // Resetear la animación
    currentFrame = 0;
    frameCounter = 0;
    
    // Configurar la duración exacta de la animación de muerte
    float deathDuration = 2.0f;
    deathTimer = Timer(deathDuration);
    deathTimer.Start();
    
    TraceLog(LOG_INFO, "Death animation started for %s (mutated: %s) with duration: %.1f seconds", 
             enemyType.c_str(), mutated ? "yes" : "no", deathDuration);
}


void Enemy::Draw() {
    // Dibujar el enemigo si tiene una textura válida
    if (texture.id != 0) {
        // Si está muriendo, añadir un poco de transparencia gradual
        Color tint = WHITE;
        if (isDying && deathTimer.GetRemainingTime() < 0.5f) {
            // Hacer más transparente en el último medio segundo
            float alpha = (deathTimer.GetRemainingTime() / 0.5f) * 255.0f;
            tint = ColorAlpha(WHITE, alpha / 255.0f);
        }
        
        DrawTextureRec(texture, frameRec, position, tint);
        
        // Debug: mostrar si está muriendo
        if (isDying) {
            DrawText("DYING", position.x, position.y - 20, 10, RED);
        }
    } else {
        TraceLog(LOG_ERROR, "Attempted to draw an invalid texture.");
    }
}

void Enemy::IncreaseSpeed() {
    if (frameSpeed < maxFrameSpeed) {
        frameSpeed++;
    }
}

void Enemy::DecreaseSpeed() {
    if (frameSpeed > minFrameSpeed) {
        frameSpeed--;
    }
}

const std::vector<Enemy*>& Enemy::GetAllInstances() {
    return allInstances;
}

void Enemy::ClearAllInstances() {
    TraceLog(LOG_INFO, "Starting to clear all enemy instances. Total instances: %zu", allInstances.size());

    // Crea una copia del vector antes de empezar a borrar
    std::vector<Enemy*> copyInstances = allInstances;
    
    // Primero limpia el vector estático (importante hacerlo antes de los delete)
    allInstances.clear();
    
    // Ahora elimina cada instancia de la copia
    for (Enemy* enemy : copyInstances) {
        if (enemy != nullptr) {
            delete enemy;
        }
    }
    
    TraceLog(LOG_INFO, "All enemy instances cleared successfully.");
}