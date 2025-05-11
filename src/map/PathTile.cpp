#include "PathTile.h"
#include "raylib.h"

PathTile::PathTile(Vector2 position, Texture2D texture)
    : Tile(position), texture(texture) {}

void PathTile::Draw() const {
    if (texture.id != 0) {
        DrawTexture(texture, position.x, position.y, WHITE);
    }
}