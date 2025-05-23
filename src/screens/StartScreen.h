#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "Screen.h"
#include "../ui/TextElement.h"
#include "../ui/Button.h"
#include "ScreenManager.h"

class StartScreen : public Screen {
private:
    TextElement title; // Título centrado
    Button startButton; // Botón de inicio
    int screenWidth;
    int screenHeight;
    ScreenManager* screenManager; // Puntero al ScreenManager

public:
    StartScreen(int screenWidth, int screenHeight, ScreenManager* screenManager);
    ~StartScreen();
    void Update() override; // Actualiza la lógica de la pantalla
    void Draw() override;   // Dibuja la pantalla
};

#endif