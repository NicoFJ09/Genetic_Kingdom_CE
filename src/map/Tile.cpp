#include "Tile.h"
#include <iostream>

Tile::Tile(bool isPath, Vector2 position, Texture2D texture, Color color)
    : isPath(isPath), position(position), texture(texture), color(color) {}

bool Tile::IsPath() const {
    return isPath;
}

void Tile::SetPath(bool path) {
    isPath = path;
}

Vector2 Tile::GetPosition() const {
    return position;
}

void Tile::SetPosition(Vector2 newPosition) {
    position = newPosition;
}

void Tile::Draw() const {
    if (isPath && texture.id != 0) {
        DrawTexture(texture, position.x, position.y, WHITE);
    } else {
        DrawRectangle(position.x, position.y, 32, 32, color);
    }
}

void Tile::CheckHover() const {
    // Define the rectangle for the tile
    Rectangle tileRect = { position.x, position.y, 32, 32 };

    // Check if the mouse is over the tile
    if (CheckCollisionPointRec(GetMousePosition(), tileRect)) {
        // Print the coordinates of the tile
        std::cout << "Tile hovered at: (" << position.x << ", " << position.y << ")" << std::endl;
    }
}