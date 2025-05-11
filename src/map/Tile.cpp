#include "Tile.h"
#include <iostream>

Tile::Tile(Vector2 position)
    : position(position) {}

Vector2 Tile::GetPosition() const {
    return position;
}

void Tile::SetPosition(Vector2 newPosition) {
    position = newPosition;
}