#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include "raylib.h"
#include "../entities/enemies/Enemy.h"
#include <vector>
#include <unordered_map>
#include <string>

class SidePanel {
private:
    Rectangle bounds; // Área del panel
    int currentWave;  // Ola actual
    float remainingTime; // Tiempo restante de la ola

    std::vector<Enemy*> activeEnemies; // Lista de enemigos activos
    int currentPage; // Página actual
    int enemiesPerPage; // Número de enemigos por página

    std::unordered_map<std::string, Texture2D> enemyTextures; // Mapa de texturas de enemigos

    // Métodos auxiliares
    void DrawEnemyInfo(Enemy* enemy, float x, float y, float width, float height);
    void DrawPaginationButtons();
    void LoadEnemyTextures(); // Cargar texturas de enemigos
    void UnloadEnemyTextures(); // Descargar texturas de enemigos

public:
    SidePanel(float x, float y, float width, float height);
    ~SidePanel();
    void UpdateWaveInfo(int wave, float time); // Actualizar información de la ola
    void SetActiveEnemies(const std::vector<Enemy*>& enemies); // Establecer enemigos activos
    void Update();    // Actualizar lógica del panel
    void Draw();      // Dibujar el panel
};

#endif // SIDE_PANEL_H