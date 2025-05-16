#include "Projectile.h"

Projectile::Projectile(Vector2 start, Vector2 end, const std::string& type, float speed)
    : position(start), target(end), towerType(type), speed(speed), active(true) {
        TraceLog(LOG_INFO, "Projectile created at (%.2f, %.2f)", position.x, position.y);
    }

void Projectile::Update(float deltaTime) {
    Vector2 dir = {target.x - position.x, target.y - position.y};
    float dist = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (dist < 1.0f) {
        active = false;
        return;
    }
    dir.x /= dist;
    dir.y /= dist;
    position.x += dir.x * speed * deltaTime;
    position.y += dir.y * speed * deltaTime;
    if (fabs(position.x - target.x) < 2.0f && fabs(position.y - target.y) < 2.0f) {
        position = target;
        active = false;
    }
}

void Projectile::Draw() const {
    DrawCircleV(position, 5, RED);
}