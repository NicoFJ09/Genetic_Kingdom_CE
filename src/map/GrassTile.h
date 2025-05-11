#ifndef GRASSTILE_H
#define GRASSTILE_H

#include "Tile.h"

class GrassTile : public Tile {
private:
    Color color;       // Color para el tile de césped
    bool isHovered;    // Indica si el tile está en hover
    bool isSelected;   // Indica si el tile está seleccionado

public:
    GrassTile(Vector2 position, Color color);
    void Draw() const override; // Sobrescribir el método Draw
    void CheckHover();          // Maneja el estado de hover
    void SetSelected(bool selected); // Cambia el estado de selección
    bool IsSelected() const;         // Devuelve si el tile está seleccionado
};

#endif // GRASSTILE_H