#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.h"
#include "../ui/TextElement.h"

class GameplayScreen : public Screen {
private:
    int screenWidth;
    int screenHeight;

public:
    GameplayScreen(int screenWidth, int screenHeight);
    void Update() override; // Actualiza la lógica de la pantalla
    void Draw() override;   // Dibuja la pantalla
};

#endif // GAMEPLAY_SCREEN_H