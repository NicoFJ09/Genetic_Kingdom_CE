#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <vector>
#include <array>
#include <memory> // Necesario para std::unique_ptr

class Map {
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles; // Cambiado a std::unique_ptr<Tile>
    std::array<Texture2D, 6> horizontalTextures; // Horizontal textures
    std::array<Texture2D, 6> verticalTextures;   // Vertical textures
    Texture2D middleTexture; // Texture for "Middle"
    Texture2D grassTexture;  // Texture for grass

public:
    Map();
    ~Map();
    Texture2D LoadAndResizeTexture(const std::string& path, int width, int height); // Load and resize texture
    void LoadFromArray(const std::array<std::array<int, 31>, 19>& mapData); // Load map data
    void Draw() const; // Draw the map
    void CheckHover() const; // Check hover for all tiles
};

#endif // MAP_H