#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.h"
#include "../ui/GamePanel.h"
#include "../ui/BottomPanel.h"
#include "../ui/SidePanel.h"
#include "../core/Game.h"

class GameplayScreen : public Screen {
private:
    int screenWidth;
    int screenHeight;

    Game game;
    GamePanel gamePanel;
    BottomPanel bottomPanel;
    SidePanel sidePanel;
    int lastWaveNumber = 0;
    // Nuevo: método para crear la tanda de enemigos
    std::vector<Enemy*> CreateWaveEnemies();

public:
    GameplayScreen(int screenWidth, int screenHeight);
    ~GameplayScreen();
    void Update() override;
    void Draw() override;
};

#endif // GAMEPLAY_SCREEN_H