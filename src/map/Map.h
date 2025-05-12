#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "GrassTile.h"
#include "TowerTile.h"
#include <vector>
#include <array>
#include <memory>

class Map {
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    std::array<Texture2D, 6> horizontalTextures;
    std::array<Texture2D, 6> verticalTextures;
    Texture2D middleTexture;
    GrassTile* selectedTile;
    TowerTile* selectedTower;

public:
    Map();
    ~Map();
    Texture2D LoadAndResizeTexture(const std::string& path, int width, int height);
    void LoadFromArray(const std::array<std::array<int, 31>, 19>& mapData);
    void Draw() const;
    void CheckHover() const;
    void HandleClick();
    GrassTile* GetSelectedTile() const;
    void UnselectTile(); // Nuevo método para deseleccionar el tile
    TowerTile* GetSelectedTower() const; // Obtener el TowerTile seleccionado
    void UnselectTower();                // Deseleccionar el TowerTile actual
    TowerTile* ReplaceTileWithTower(GrassTile* oldTile, const std::string& towerType, int level);
};

#endif // MAP_H