#ifndef DEFEAT_SCREEN_H
#define DEFEAT_SCREEN_H

#include "Screen.h"
#include "../ui/TextElement.h"
#include "../ui/Button.h"
#include "ScreenManager.h"

class DefeatScreen : public Screen {
private:
    TextElement title; // Título centrado
    Button backButton; // Botón de inicio
    int screenWidth;
    int screenHeight;
    ScreenManager* screenManager; // Puntero al ScreenManager

public:
    DefeatScreen(int screenWidth, int screenHeight, ScreenManager* screenManager);
    ~DefeatScreen();
    void Update() override; // Actualiza la lógica de la pantalla
    void Draw() override;   // Dibuja la pantalla
};

#endif