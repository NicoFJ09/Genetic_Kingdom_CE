#include "Tower.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>
#include <memory>

std::vector<Tower*> Tower::allInstances;

Tower::Tower(Vector2 position, int level, const std::string& path, int damage, int speed, int range, int spAttackRegenerationTime)
    : position(position), level(level), texturePath(path), damage(damage), speed(speed), range(range),
       spAttackRegenerationTime(spAttackRegenerationTime), centerPos({position.x + 16.0f, position.y + 16.0f})

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

void Tower::Update(float deltaTime)
{
    // Insertar lógica de targetear enemigos, cooldown de ataque,
    // y actualizar atributos de instancia en caso de subir de nivel
    UpdateProjectiles(deltaTime);
}

void Tower::Draw()
{
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
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

Vector2 GetTileCenter(int tileX, int tileY) {
    return { tileX * 32.0f + 16.0f, tileY * 32.0f + 16.0f };
}

void Tower::AttackEnemy() {
    Vector2 start = centerPos; // Should be (3*32+16, 4*32+16)
    Vector2 end = GetTileCenter(1, 1); // Enemy position in tile coordinates
    FireAt(end);
}

void Tower::FireAt(const Vector2& target) {
    projectiles.push_back(std::make_unique<Projectile>(centerPos, target, towerType, 100.0f));
    TraceLog(LOG_INFO, "Firing projectile from (%.2f, %.2f) to (%.2f, %.2f)", centerPos.x, centerPos.y, target.x, target.y);
}

void Tower::UpdateProjectiles(float deltaTime) {
    for (auto& proj : projectiles) {
        if (proj->active)
            proj->Update(deltaTime);
    }
    // Remove inactive projectiles
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
        [](const std::unique_ptr<Projectile>& p) { return !p->active; }),
        projectiles.end());
}

void Tower::DrawProjectiles() const {
    for (const auto& proj : projectiles) {
        if (proj->active)
            proj->Draw();
    }
}