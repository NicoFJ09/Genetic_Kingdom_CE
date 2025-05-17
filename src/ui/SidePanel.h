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
    int enemiesKilled; // Nuevo: Contador de enemigos eliminados

    // Vectores específicos por tipo de enemigo (reemplaza el vector general)
    std::vector<Enemy*> ogres;
    std::vector<Enemy*> harpies;
    std::vector<Enemy*> mercenaries;
    std::vector<Enemy*> darkElves;
    
    int currentPageIndex; // Índice de la página actual
    std::vector<std::string> enemyTypes; // Tipos de enemigos (Ogre, Harpy, etc.)
    std::unordered_map<std::string, Texture2D> enemyTextures; 
    
    // Métodos auxiliares
    void DrawEnemyInfo(Enemy* enemy, float x, float y, float width, float height);
    void DrawPaginationButtons();

public:
    SidePanel(float x, float y, float width, float height);
    ~SidePanel();
    
    // Actualizar con ambos datos: ola y enemigos eliminados
    void UpdateWaveInfo(int wave, int killedEnemies = 0);
    
    // Reemplazar este método con uno que acepta los 4 vectores
    void SetEnemyVectors(
        const std::vector<Enemy*>& ogres,
        const std::vector<Enemy*>& harpies,
        const std::vector<Enemy*>& mercenaries,
        const std::vector<Enemy*>& darkElves
    );
    
    void Update();
    void Draw();
};

#endif // SIDE_PANEL_H