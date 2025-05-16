#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"
#include <string>
#include <cmath>
#include <vector>

class Projectile {
public:
    Vector2 position;
    Vector2 target;
    std::string towerType;
    float speed;
    bool active;

    Projectile(Vector2 start, Vector2 end, const std::string& type, float speed = 300.0f);

    void Update(float deltaTime);
    void Draw() const;
};

#endif