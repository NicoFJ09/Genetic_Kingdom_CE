#ifndef GRASSTILE_H
#define GRASSTILE_H

#include "Tile.h"

class GrassTile : public Tile {
private:
    Color color;       // Color para el tile de césped
    bool isHovered;    // Indica si el tile está en hover

public:
    GrassTile(Vector2 position, Color color);
    void Draw() const override; // Sobrescribir el método Draw
    void CheckHover();          // Método exclusivo para GrassTile
};

#endif // GRASSTILE_H