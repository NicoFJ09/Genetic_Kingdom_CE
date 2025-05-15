#include "Tower.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>

std::vector<Tower*> Tower::allInstances;

Tower::Tower(Vector2 position, int level, const std::string& path, int damage, double speed, int range, int spAttackRegenerationTime)
    : position(position), level(level), texturePath(path), damage(damage), speed(speed), range(range),
       spAttackRegenerationTime(spAttackRegenerationTime)
{
    texture = LoadAndResizeTexture(texturePath.c_str(), 32, 32); // Example width and height
    allInstances.push_back(this);
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
    // Insertar lógica de targetear enemigos, cooldown de ataque,
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