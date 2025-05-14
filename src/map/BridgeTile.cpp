#include "BridgeTile.h"
#include "raylib.h"

BridgeTile::BridgeTile(Vector2 position, Texture2D texture)
    : Tile(position), texture(texture) {}

void BridgeTile::Draw() const {
    if (texture.id != 0) {
        DrawTexture(texture, position.x, position.y, WHITE);
    }
}