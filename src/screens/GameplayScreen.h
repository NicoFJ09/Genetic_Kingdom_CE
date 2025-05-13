#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.h"
#include "../ui/GamePanel.h"
#include "../ui/BottomPanel.h"
#include "../ui/SidePanel.h"
#include "../core/Game.h"
#include "../entities/enemies/Enemy.h"
#include <vector>

class GameplayScreen : public Screen {
private:
    int screenWidth;
    int screenHeight;

    Game game; // Instancia de Game
    GamePanel gamePanel;
    BottomPanel bottomPanel;
    SidePanel sidePanel;

    std::vector<Enemy*> enemies; // Contenedor para manejar enemigos

public:
    GameplayScreen(int screenWidth, int screenHeight);
    ~GameplayScreen();
    void Update() override; // Actualizar la lógica de la pantalla
    void Draw() override;   // Dibujar la pantalla
};

#endif // GAMEPLAY_SCREEN_H