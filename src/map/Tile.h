#ifndef TILE_H
#define TILE_H

#include "raylib.h"

class Tile {
private:
    bool isPath; // True if the tile is a path, false if it's grass
    Vector2 position; // Position of the tile on the map
    Texture2D texture; // Texture for path tiles
    Color color; // Color for grass tiles

public:
    Tile(bool isPath, Vector2 position, Texture2D texture = {0}, Color color = {0, 0, 0, 0});

    bool IsPath() const;
    void SetPath(bool path);

    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPosition);

    void Draw() const; // Draw the tile
    void CheckHover() const; // Check if the mouse is hovering over the tile
};

#endif // TILE_H