#include "BridgeTile.h"
#include "raylib.h"

BridgeTile::BridgeTile(Vector2 position, Texture2D texture)
    : Tile(position), texture(texture) {}

void BridgeTile::Draw() const {
    if (texture.id != 0) {
        DrawTexture(texture, position.x, position.y, WHITE);
    }
}

bool BridgeTile::CheckEnemyCollision(const std::vector<Enemy*>& enemies) const {
    // Tamaño del tile para detección de colisión
    float tileSize = 32.0f;
    Rectangle bridgeRect = {position.x, position.y, tileSize, tileSize};
    
    for (const Enemy* enemy : enemies) {
        if (enemy && enemy->IsActive()) {
            Vector2 enemyPos = enemy->GetPosition();
            Rectangle enemyRect = {enemyPos.x, enemyPos.y, tileSize, tileSize};
            
            if (CheckCollisionRecs(bridgeRect, enemyRect)) {
                TraceLog(LOG_WARNING, "Enemy %s reached the bridge!", enemy->GetEnemyType().c_str());
                return true;
            }
        }
    }
    return false;
}

bool BridgeTile::IsUnderAttack(const std::vector<Enemy*>& enemies) const {
    return CheckEnemyCollision(enemies);
}