#ifndef TOWERTILE_H
#define TOWERTILE_H

#include "Tile.h"
#include "../entities/towers/Tower.h"
#include "raylib.h"

class TowerTile : public Tile {
private:
    Tower* tower; // Instancia de Tower colocada en el tile

public:
    TowerTile(Vector2 position, Tower* tower = nullptr);
    ~TowerTile();

    void SetTower(Tower* newTower); // Asignar una nueva torre al tile
    Tower* GetTower() const;        // Obtener la torre actual
    void RemoveTower();             // Eliminar la torre actual

    void Draw() const override;     // Sobrescribir el método Draw
};

#endif // TOWERTILE_H