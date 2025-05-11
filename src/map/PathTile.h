#ifndef PATHTILE_H
#define PATHTILE_H

#include "Tile.h"

class PathTile : public Tile {
private:
    Texture2D texture; // Textura para el tile de camino

public:
    PathTile(Vector2 position, Texture2D texture);
    void Draw() const override; // Sobrescribir el método Draw
};

#endif // PATHTILE_H