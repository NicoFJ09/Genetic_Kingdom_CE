#ifndef TOWERTILE_H
#define TOWERTILE_H

#include "Tile.h"
#include "raylib.h"

class TowerTile : public Tile {
private:
    Texture2D texture; // Textura del tile de la torre

public:
    TowerTile(Vector2 position, Color color);
    ~TowerTile();
    void Draw() const override; // Sobrescribir el método Draw
};

#endif // TOWERTILE_H