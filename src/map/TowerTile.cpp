#include "TowerTile.h"
#include "raylib.h"

TowerTile::TowerTile(Vector2 position, Color color)
    : Tile(position) {
    // Generar una imagen con el color especificado
    Image image = GenImageColor(32, 32, color); // Tamaño de la textura: 32x32
    texture = LoadTextureFromImage(image);      // Crear la textura a partir de la imagen
    UnloadImage(image);                         // Liberar la imagen, ya no es necesaria
}

TowerTile::~TowerTile() {
    UnloadTexture(texture); // Liberar la textura cuando se destruye el tile
}

void TowerTile::Draw() const {
    // Dibujar el tile de la torre con la textura generada
    DrawTexture(texture, position.x, position.y, WHITE);
}