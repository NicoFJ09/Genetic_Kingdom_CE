#include "Enemy.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>

// Inicialización del contenedor estático
std::vector<Enemy*> Enemy::allInstances;
int Enemy::currentGeneration = 1; // Generación inicial

Enemy::Enemy(bool alive, Vector2 pos, int speed, const std::string& path, int frames,
             const std::string& enemyType, int health, int speedValue, int arrowResistance,
             int magicResistance, int artilleryResistance, bool mutated)
    : isAlive(alive), position(pos), frameSpeed(speed > 0 ? speed : 1), currentFrame(0), frameCounter(0),
      frameCount(frames), texturePath(path), enemyType(enemyType), health(health), speed(speedValue),
      arrowResistance(arrowResistance), magicResistance(magicResistance), artilleryResistance(artilleryResistance),
      mutated(mutated), generation(currentGeneration) {
    texture = LoadTexture(texturePath.c_str());
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture: %s", texturePath.c_str());
        frameRec = {0.0f, 0.0f, 0.0f, 0.0f};
    } else {
        frameRec = {0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height};
    }

    // Agregar la instancia al contenedor estático
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

// Métodos estáticos
void Enemy::SetCurrentGeneration(int generation) {
    currentGeneration = generation;
}

int Enemy::GetCurrentGeneration() {
    return currentGeneration;
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

// Métodos existentes
void Enemy::Update() {
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