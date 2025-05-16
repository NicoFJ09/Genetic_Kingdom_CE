#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.h"
#include "../ui/GamePanel.h"
#include "../ui/BottomPanel.h"
#include "../ui/SidePanel.h"
#include "../core/Game.h"
#include "ScreenManager.h"
#include "../map/BridgeTile.h"

class GameplayScreen : public Screen {
private:
    int screenWidth;
    int screenHeight;
    ScreenManager* screenManager; // Agregar puntero al ScreenManager

    Game game;
    GamePanel gamePanel;
    BottomPanel bottomPanel;
    SidePanel sidePanel;
    int lastWaveNumber = 0;
    BridgeTile* bridgeTile = nullptr; // Puntero al BridgeTile para detectar colisiones
    
    // Nuevo: método para crear la tanda de enemigos
    std::vector<Enemy*> CreateWaveEnemies();
    
    // Nuevo: método para verificar derrota
    void CheckForDefeat();

public:
    GameplayScreen(int screenWidth, int screenHeight, ScreenManager* screenManager);
    ~GameplayScreen();
    void Update() override;
    void Draw() override;
};

#endif // GAMEPLAY_SCREEN_H