#include "Enemy.h"
#include "raylib.h"
#include <iostream>

Enemy::Enemy(bool alive, Vector2 pos, int speed, const std::string& path, int frames)
    : isAlive(alive), position(pos), frameSpeed(speed > 0 ? speed : 1), currentFrame(0), frameCounter(0), frameCount(frames), texturePath(path) {
    texture = LoadTexture(texturePath.c_str());
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture: %s", texturePath.c_str());
        frameRec = {0.0f, 0.0f, 0.0f, 0.0f};
    } else {
        frameRec = {0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height};
    }
}

Enemy::~Enemy() {
    if (texture.id != 0) {
        UnloadTexture(texture);
    }
}

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