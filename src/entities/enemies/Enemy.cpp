#include "Enemy.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>
#include <cmath>

// Inicialización del contenedor estático
std::vector<Enemy*> Enemy::allInstances;

Enemy::Enemy(bool alive, Vector2 pos, int frameSpeed, const std::string& texturePath, int frameCount,
             const std::string& enemyType, int health, int speed, int arrowResistance,
             int magicResistance, int artilleryResistance, bool mutated, int generation, int mutationChance)
    : isAlive(alive), position(pos), frameSpeed(frameSpeed > 0 ? frameSpeed : 1), currentFrame(0), frameCounter(0),
      frameCount(frameCount), texturePath(texturePath), enemyType(enemyType), health(health), speed(speed),
      arrowResistance(arrowResistance), magicResistance(magicResistance), artilleryResistance(artilleryResistance),
      mutated(mutated), generation(generation), mutationChance(mutationChance),
      currentPathIndex(0), interpolationFactor(0.0f), isActive(false) {
    texture = LoadTexture(texturePath.c_str());
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture: %s", texturePath.c_str());
        frameRec = {0.0f, 0.0f, 0.0f, 0.0f};
    } else {
        frameRec = {0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height};
    }
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

int Enemy::GetHealth() const {
    return health;
}

void Enemy::SetHealth(int healthValue) {
    health = healthValue;
}

int Enemy::GetSpeed() const {
    return speed;
}

void Enemy::SetSpeed(int speedValue) {
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
    PathMove(deltaTime);
    if (frameSpeed <= 0) {
        TraceLog(LOG_ERROR, "Invalid frameSpeed: %d", frameSpeed);
        frameSpeed = 1; // Valor por defecto
    }

    frameCounter++;

    if (frameCounter >= (60 / frameSpeed)) {
        frameCounter = 0;

        if (isAlive) {
            currentFrame = (currentFrame + 1) % frameCount;
        } else {
            if (currentFrame < frameCount - 1) {
                currentFrame++;
            }
        }

        frameRec.x = (float)currentFrame * frameRec.width;
    }
}

void Enemy::Draw() {
    if (texture.id != 0) {
        DrawTextureRec(texture, frameRec, position, WHITE);
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

void Enemy::ClearAllInstances() {
    TraceLog(LOG_INFO, "Starting to clear all enemy instances. Total instances: %zu", allInstances.size());

    for (size_t i = 0; i < allInstances.size(); ++i) {
        Enemy* enemy = allInstances[i];
        if (enemy != nullptr) {
            TraceLog(LOG_INFO, "Deleting enemy instance at index %zu", i);
            delete enemy; // Liberar memoria de cada instancia
        } else {
            TraceLog(LOG_ERROR, "Encountered a nullptr at index %zu in allInstances", i);
        }
    }

    allInstances.clear(); // Vaciar el contenedor
    TraceLog(LOG_INFO, "All enemy instances cleared successfully.");
}