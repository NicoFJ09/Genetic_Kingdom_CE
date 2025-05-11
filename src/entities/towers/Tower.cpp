#include "Tower.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>

std::vector<Tower*> Tower::allInstances;

Tower::Tower(Vector2 position, int level, const std::string& path, int damage, int speed, int range,
             int attackRegenerationTime, int spAttackRegenerationTime)
    : position(position), level(1), texturePath(path), damage(10), speed(1), range(100),
      attackRegenerationTime(60), spAttackRegenerationTime(180)
{
    texture = LoadTexture(texturePath.c_str());
    allInstances.push_back(this);
}

Tower::~Tower()
{
    UnloadTexture(texture);

    // Remove this instance from the static list
    auto it = std::find(allInstances.begin(), allInstances.end(), this);
    if (it != allInstances.end()) {
        allInstances.erase(it);
    }
}

void Tower::Update()
{
    // Insertar logica de targetear enemigos, cooldown de ataque,
    // y actualizar atributos de instancia en caso de subir de nivel
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