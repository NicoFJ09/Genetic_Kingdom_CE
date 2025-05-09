#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.h"
#include "../ui/GamePanel.h"
#include "../ui/BottomPanel.h"
#include "../ui/SidePanel.h"

class GameplayScreen : public Screen {
private:
    int screenWidth;
    int screenHeight;

    GamePanel gamePanel;
    BottomPanel bottomPanel;
    SidePanel sidePanel;

public:
    GameplayScreen(int screenWidth, int screenHeight);
    void Update() override; // Actualizar la lógica de la pantalla
    void Draw() override;   // Dibujar la pantalla
};

#endif // GAMEPLAY_SCREEN_H