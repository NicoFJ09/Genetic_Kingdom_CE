#include "TowerTile.h"

TowerTile::TowerTile(Vector2 position, Tower* tower)
    : Tile(position), tower(tower) {}

TowerTile::~TowerTile() {
    delete tower; // Liberar la torre si se elimina el tile
}

void TowerTile::SetTower(Tower* newTower) {
    delete tower; // Liberar la torre anterior
    tower = newTower;
}

Tower* TowerTile::GetTower() const {
    return tower;
}

void TowerTile::RemoveTower() {
    delete tower; // Liberar la torre actual
    tower = nullptr;
}

void TowerTile::Draw() const {
    // Dibujar el tile
    DrawRectangle(position.x, position.y, 32, 32, GRAY);

    // Dibujar la torre si existe
    if (tower) {
        tower->Draw();
    }
}