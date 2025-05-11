#ifndef TILE_H
#define TILE_H

#include "raylib.h"

class Tile {
protected:
    Vector2 position; // Posición del tile en el mapa

public:
    Tile(Vector2 position);
    virtual ~Tile() = default;

    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPosition);

    virtual void Draw() const = 0; // Método virtual puro para dibujar
};

#endif // TILE_H