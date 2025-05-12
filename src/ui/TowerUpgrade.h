#ifndef TOWERUPGRADE_H
#define TOWERUPGRADE_H

#include "../core/EconomySystem.h"
#include "../map/TowerTile.h"
#include "raylib.h"
#include <string>
#include <unordered_map>

class TowerUpgrade {
private:
    bool isVisible;           // Estado de visibilidad
    bool isButtonPressed;     // Estado del botón de mejora
    Rectangle bounds;         // Dimensiones del panel inferior
    EconomySystem& economySystem;

    std::unordered_map<std::string, std::unordered_map<int, Texture2D>> towerTextures; // Texturas por tipo y nivel

    void HandleUpgrade(TowerTile*& selectedTower); // Manejar la lógica de mejora
    void LoadTowerTextures(); // Cargar las texturas de las torres

public:
    TowerUpgrade(float panelX, float panelY, float panelWidth, float panelHeight, EconomySystem& economySystem);
    ~TowerUpgrade(); // Liberar texturas
    void Update(TowerTile*& selectedTower); // Actualizar la lógica de mejora
    void Draw(TowerTile* selectedTower);   // Dibujar la pantalla de mejora
};

#endif // TOWERUPGRADE_H